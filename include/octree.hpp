#ifndef OCTREE_HPP
#define OCTREE_HPP

#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <array>
#include "vector.hpp"
#include "bounding_objs.hpp"

//TODO: the bounding boxes are a power of two - an integer. Do it.

namespace octree {

class OctTree_t {
    
    std::list<lingeo::Triangle_t> objects_;

    std::vector<OctTree_t *> child_node;

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
            octant.emplace_back(lingeo::Vector3(center.x(), region_.min().y(), region_.min().z()),    lingeo::Vector3(region_.max().x(), center.y(), center.z()));
            octant.emplace_back(lingeo::Vector3(center.x(), region_.min().y(), center.z()),           lingeo::Vector3(region_.max().x(), center.y(), region_.max().z()));
            octant.emplace_back(lingeo::Vector3(region_.min().x(), region_.min().y(), center.z()),  lingeo::Vector3(center.x(), center.y(), region_.max().z()));
            octant.emplace_back(lingeo::Vector3(region_.min().x(), center.y(), region_.min().z()),  lingeo::Vector3(center.x(), region_.max().y(), center.z()));
            octant.emplace_back(lingeo::Vector3(center.x(), center.y(), region_.min().z()),         lingeo::Vector3(region_.max().x(), region_.max().y(), center.z()));
            octant.emplace_back(center, region_.max());
            octant.emplace_back(lingeo::Vector3(region_.min().x(), center.y(), center.z()),         lingeo::Vector3(center.x(), region_.max().y(), region_.max().z()));

            std::array<std::vector<lingeo::Triangle_t>, 8> oct_array{};

            std::vector<tr_vec_it> del_list;

            for (tr_list_it it = objects_.begin(), ite = objects_.end(); it != ite; ++it)
            {
                if (it->get_min_vec_in_bounding_box() != it->get_max_vec_in_bounding_box())
                {
                    for (int a = 0; a < 8; ++a)
                    {
                        if (octant[a].contains(it->get_bounding_box()))
                        {
                            oct_array[a].push_back(*it);
                            objects_.erase(it);
                            break;
                        }
                    }
                }
            }
            
            for (int a = 0; a < 8; a++)
            {
                if (!oct_array[a].empty())
                {
                    child_node[a] = create_node(octant[a], oct_array[a]);
                    if (child_node[a] != nullptr)
                    {
                        child_node[a]->build_tree();
                    }
                }
            }

            is_tree_built = true;
            is_tree_ready = true;
        }

        OctTree_t *create_node(lingeo::Bounding_box &region, std::vector<lingeo::Triangle_t> &objects)
        {
            if (!objects.empty())
                return nullptr;
            
            OctTree_t *ret = new OctTree_t(region, objects.begin(), objects.end());
            ret->parent_ = this;

            return ret;   
        }

        size_t count_tr_intersection(std::list<lingeo::Triangle_t> &parent_objs)
        {
            size_t num_intersections = 0;
            for (auto p_obj : parent_objs)
            {
                for (auto l_obj : objects_)
                {
                    if(lingeo::intersection_3D_triangles(l_obj, p_obj))
                    {
                        num_intersections++;
                    }
                }
            }

            if (objects_.size() > 1)
            {
                std::list<lingeo::Triangle_t> tmp = objects_;
                tr_list_it tmp_it = tmp.begin();
                while (tmp.size() > 0)
                {
                    for (tr_list_it l_obj_2 = tmp.begin(), ite = tmp.end(); l_obj_2 != ite; ++l_obj_2)
                    {
                        tmp_it = std::prev(tmp.end()); //TODO: raise one level up
                        if (tmp_it == l_obj_2)
                            continue;
                        if (lingeo::intersection_3D_triangles(*tmp_it, *l_obj_2))
                        {
                            num_intersections++;
                        }
                    }
                    tmp.pop_back();
                }
            }

            // parent_objs.append_range(objects_);
            for (auto l_obj : objects_) //TODO: enable standard 23
                parent_objs.push_back(l_obj);

            for (int i = 0; i < 8; ++i)
            {
                if (!child_node.empty() && child_node[i] != nullptr)
                {
                    num_intersections += child_node[i]->count_tr_intersection(parent_objs);
                }
            }
            return num_intersections;
        }
};

} /* namespace octree */


#endif