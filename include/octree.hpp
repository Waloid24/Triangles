#ifndef OCTREE_HPP
#define OCTREE_HPP

#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <array>
#include <iterator>
#include "vector.hpp"
#include "bounding_objs.hpp"

namespace octree {

class OctTree_t {
    
    std::list<lingeo::Triangle> objects_;

    std::array<OctTree_t *, 8> child_node_{};

    static constexpr int MIN_SIZE_ = 1;

    OctTree_t *parent_;

    lingeo::Bounding_box region_;

    using tr_vec_it = typename std::vector<lingeo::Triangle>::iterator;
    using tr_list_it = typename std::list<lingeo::Triangle>::iterator;

    public:

        template<class iter>
        OctTree_t(const lingeo::Bounding_box &region, iter begin, iter end) : region_{region} {
            
            for (; begin != end; ++begin)
            {
                objects_.push_back(*begin);
            }
        }

        size_t count_intersection_in_octree()
        {
            size_t num_intersections = 0;
            
            build_tree();

            num_intersections += check_intersection_btw_objs();

            for (int i = 0; i < 8; ++i)
            {
                if (child_node_[i] != nullptr)
                {
                    num_intersections += child_node_[i]->count_intersection(objects_);
                }
            }

            return num_intersections;
        }

    private:
        
        void build_tree()
        {
            if (objects_.size() <= 1)
            {
                return;
            }

            lingeo::Vector3 dimensions = region_.max() - region_.min();

            if (dimensions.is_null())
            {
                region_.find_enclosing_cube();
                dimensions = region_.max() - region_.min();
            }

            if (dimensions.x() <= MIN_SIZE_ && dimensions.y() <= MIN_SIZE_ && dimensions.z() <= MIN_SIZE_)
            {
                return;
            }

            lingeo::Vector3 half = dimensions / 2.0f;
            lingeo::Vector3 center = region_.min() + half;

            std::vector<lingeo::Bounding_box> octant;
            octant.emplace_back(region_.min(), center);

            octant.emplace_back(center, region_.max());

            octant.emplace_back(center.x(), region_.min().y(), region_.min().z(),
                                region_.max().x(), center.y(), center.z());

            octant.emplace_back(center.x(), region_.min().y(), center.z(),
                                region_.max().x(), center.y(), region_.max().z());

            octant.emplace_back(region_.min().x(), region_.min().y(), center.z(),  
                                center.x(), center.y(), region_.max().z());

            octant.emplace_back(region_.min().x(), center.y(), region_.min().z(),  
                                center.x(), region_.max().y(), center.z());

            octant.emplace_back(center.x(), center.y(), region_.min().z(),
                                region_.max().x(), region_.max().y(), center.z());

            octant.emplace_back(region_.min().x(), center.y(), center.z(),
                                center.x(), region_.max().y(), region_.max().z());

            std::array<std::vector<lingeo::Triangle>, 8> oct_array;

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
                    child_node_[a] = new_tree; 
                    child_node_[a]->parent_ = this;

                    if (child_node_[a] != nullptr)
                    {
                        child_node_[a]->build_tree();
                    }
                }
            }
        }

        size_t check_intersection_btw_objs()
        {
            size_t num_intersections = 0;

            if (objects_.size() > 1)
            {
                std::list<lingeo::Triangle> tmp = objects_;
                tr_list_it tmp_it = tmp.begin();
                while (tmp.size() > 0)
                {
                    for (tr_list_it l_obj_2 = tmp.begin(), ite = tmp.end(); l_obj_2 != ite; ++l_obj_2)
                    {
                        tmp_it = std::prev(tmp.end());
                        if (tmp_it == l_obj_2)
                            continue;
                        if (lingeo::triangles_intersection(*tmp_it, *l_obj_2))
                        {
                            num_intersections++;
                            // std::cout << "OBJS AND OBJS:" << std::endl;
                            // std::cout << "obj1: ";
                            // (*tmp_it).print();
                            // std::cout << "obj2: ";
                            // (*l_obj_2).print();
                        }
                    }
                    tmp.pop_back();
                }
            }

            return num_intersections;
        }

        size_t check_intersection_btw_parent_objs_loc_objs(std::list<lingeo::Triangle> &parent_objs)
        {
            size_t num_intersections = 0;

            for (auto p_obj : parent_objs)
            {
                for (auto l_obj : objects_)
                {
                    if(lingeo::triangles_intersection(l_obj, p_obj))
                    {
                        // std::cout << "PARENT AND CHILD:" << std::endl;
                        // std::cout << "parent: ";
                        // p_obj.print();
                        // std::cout << "child: ";
                        // l_obj.print();
                        num_intersections++;
                    }
                }
            }

            return num_intersections;
        }

        
        size_t count_intersection(std::list<lingeo::Triangle> &parent_objs)
        {
            size_t num_intersections = 0;

            num_intersections += check_intersection_btw_parent_objs_loc_objs(parent_objs);

            num_intersections += check_intersection_btw_objs();

            std::copy(objects_.begin(), objects_.end(), std::back_inserter(parent_objs));

            for (auto ptr : child_node_)
            {
                if (ptr)
                    num_intersections += ptr->count_intersection(parent_objs);
            }

            return num_intersections;
        }
};

} /* namespace octree */


#endif