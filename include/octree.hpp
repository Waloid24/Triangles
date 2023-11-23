#ifndef OCTREE_HPP
#define OCTREE_HPP

#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <array>
#include "vector.hpp"
#include "bounding_objs.hpp"

namespace octree {

class OctTree_t {
    
    std::list<lingeo::Triangle_t> objects_;

    std::array<OctTree_t *, 8> child_node{};

    const int MIN_SIZE = 1;

    OctTree_t *parent_;

    lingeo::Bounding_box region_;

    std::queue<lingeo::Triangle_t> pendingInsertion;

    bool is_tree_built = false;
    bool is_tree_ready = false;


    using tr_vec_it = typename std::vector<lingeo::Triangle_t>::iterator;
    using tr_list_it = typename std::list<lingeo::Triangle_t>::iterator;

    public:

        OctTree_t(lingeo::Bounding_box region, tr_vec_it begin, tr_vec_it end) : region_{region} {

            for (tr_vec_it it = begin, ite = end; it != ite; ++it)
            {
                pendingInsertion.push(*it);
            }
        }

        size_t count_intersection_in_octree()
        {
            size_t num_intersections = 0;

            update_tree();

            check_intersection_btw_objs(&num_intersections);

            for (int i = 0; i < 8; ++i)
            {
                if (!child_node.empty() && child_node[i] != nullptr)
                {
                    child_node[i]->count_intersection(objects_, &num_intersections);
                }
            }

            return num_intersections;
        }

    private:

        void update_tree()
        {
            if (!is_tree_built)
            {
                while (pendingInsertion.size() != 0)
                {
                    objects_.push_back(pendingInsertion.front());
                    pendingInsertion.pop();
                }
                build_tree();
            }
            else
            {
                while (pendingInsertion.size() != 0)
                {
                    #if 0
                    insert(pendingInsertion.front());
                    pendingInsertion.pop();
                    #endif
                    
                    #if 1
                    std::cout << "You should realise insert() function!" << std::endl;
                    #endif
                }
            }
            is_tree_ready = true;
        }
        
        void build_tree()
        {
            if (objects_.size() <= 1)
            {
                return;
            }

            lingeo::Vector3 dimensions = region_.max() - region_.min();

            if (dimensions == lingeo::Vector3{0})
            {
                region_.find_enclosing_cube();
                dimensions = region_.max() - region_.min();
            }

            if (dimensions.x() <= MIN_SIZE && dimensions.y() <= MIN_SIZE && dimensions.z() <= MIN_SIZE)
            {
                return;
            }

            lingeo::Vector3 half = dimensions / 2.0f;
            lingeo::Vector3 center = region_.min() + half;

            std::vector<lingeo::Bounding_box> octant;
            octant.emplace_back(region_.min(), center);
            octant.emplace_back(lingeo::Vector3(center.x(), region_.min().y(), region_.min().z()),  lingeo::Vector3(region_.max().x(), center.y(), center.z()));
            octant.emplace_back(lingeo::Vector3(center.x(), region_.min().y(), center.z()),         lingeo::Vector3(region_.max().x(), center.y(), region_.max().z()));
            octant.emplace_back(lingeo::Vector3(region_.min().x(), region_.min().y(), center.z()),  lingeo::Vector3(center.x(), center.y(), region_.max().z()));
            octant.emplace_back(lingeo::Vector3(region_.min().x(), center.y(), region_.min().z()),  lingeo::Vector3(center.x(), region_.max().y(), center.z()));
            octant.emplace_back(lingeo::Vector3(center.x(), center.y(), region_.min().z()),         lingeo::Vector3(region_.max().x(), region_.max().y(), center.z()));
            octant.emplace_back(center, region_.max());
            octant.emplace_back(lingeo::Vector3(region_.min().x(), center.y(), center.z()),         lingeo::Vector3(center.x(), region_.max().y(), region_.max().z()));

            std::array<std::vector<lingeo::Triangle_t>, 8> oct_array;

            std::vector<tr_list_it> del_list;

            for (tr_list_it it = objects_.begin(), ite = objects_.end(); it != ite; ++it)
            {
                if (it->get_min_vec_in_bounding_box() != it->get_max_vec_in_bounding_box())
                {
                    for (int a = 0; a < 8; ++a)
                    {
                        if (octant[a].contains(it->get_bounding_box()))
                        {
                            oct_array[a].push_back(*it);
                            del_list.push_back(it);
                            break;
                        }
                    }
                }
            }

            for (auto obj : del_list)
            {
                objects_.erase(obj);
            }
            
            for (int a = 0; a < 8; a++)
            {
                if (!oct_array[a].empty())
                {
                    OctTree_t *new_tree = new OctTree_t{octant[a], oct_array[a].begin(), oct_array[a].end()};
                    child_node[a] = new_tree; 
                    child_node[a]->parent_ = this;

                    if (child_node[a] != nullptr)
                    {
                        child_node[a]->build_tree();
                    }
                }
            }

            is_tree_built = true;
            is_tree_ready = true;
        }

        void check_intersection_btw_objs(size_t *num_intersections)
        {
            if (objects_.size() > 1)
            {
                std::list<lingeo::Triangle_t> tmp = objects_;
                tr_list_it tmp_it = tmp.begin();
                while (tmp.size() > 0)
                {
                    for (tr_list_it l_obj_2 = tmp.begin(), ite = tmp.end(); l_obj_2 != ite; ++l_obj_2)
                    {
                        tmp_it = std::prev(tmp.end());
                        if (tmp_it == l_obj_2)
                            continue;
                        if (lingeo::intersection_3D_triangles(*tmp_it, *l_obj_2))
                        {
                            (*num_intersections)++;
                        }
                    }
                    tmp.pop_back();
                }
            }
        }

        void check_intersection_btw_parent_objs_loc_objs(std::list<lingeo::Triangle_t> &parent_objs, size_t *num_intersections)
        {
            for (auto p_obj : parent_objs)
            {
                for (auto l_obj : objects_)
                {
                    if(lingeo::intersection_3D_triangles(l_obj, p_obj))
                    {
                        (*num_intersections)++;
                    }
                }
            }
        }

        void count_intersection(std::list<lingeo::Triangle_t> &parent_objs, size_t *num_intersections)
        {            
            check_intersection_btw_parent_objs_loc_objs(parent_objs, num_intersections);

            check_intersection_btw_objs(num_intersections);

            // parent_objs.append_range(objects_); //TODO: enable standard 23
            for (auto l_obj : objects_) 
                parent_objs.push_back(l_obj);

            for (int i = 0; i < 8; ++i)
            {
                if (!child_node.empty() && child_node[i] != nullptr)
                {
                    child_node[i]->count_intersection(parent_objs, num_intersections);
                }
            }
        }
};

} /* namespace octree */


#endif