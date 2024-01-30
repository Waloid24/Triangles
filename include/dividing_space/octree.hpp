#ifndef OCTREE_HPP
#define OCTREE_HPP

#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <array>
#include <iterator>
#include "../primitives/vector.hpp"
#include "bounding_objs.hpp"
#include "shape.hpp"
#include "../intersections/intersection_driver.hpp"

namespace octree {

class OctTree_t {
    
    std::list<lingeo::Shape> objects_;

    std::array<OctTree_t *, 8> child_node_{};

    static constexpr int MIN_SIZE_ = 1;

    OctTree_t *parent_;

    lingeo::Bounding_box region_;

    using shapes_iter = typename std::list<lingeo::Shape>::iterator;

    public:

        template<class iter>
        OctTree_t(const lingeo::Bounding_box &region, iter begin, iter end) : region_{region} {
            
            for (; begin != end; ++begin)
                objects_.push_back(*begin);

        }

        size_t count_intersection_in_octree()
        {
            size_t num_intersections = 0;
            
            build_tree();

            num_intersections += check_intersection_btw_objs();

            for (auto elem : child_node_)
            {
                if (elem != nullptr)
                    num_intersections += elem->count_intersection(objects_);
            }

            return num_intersections;
        }

    private:
        
        void build_tree()
        {
            if (objects_.size() <= 1)
                return;

            lingeo::Vector dimensions = region_.max() - region_.min();

            if (dimensions.is_null())
            {
                region_.find_border();
                dimensions = region_.max() - region_.min();
            }

            if (dimensions.x() <= MIN_SIZE_ && dimensions.y() <= MIN_SIZE_ && dimensions.z() <= MIN_SIZE_)
                return;

            lingeo::Vector half = dimensions / 2.0f;
            lingeo::Vector center = region_.min() + half;

            std::vector<lingeo::Bounding_box> octant;
            octant.emplace_back(region_.min(), center);

            octant.emplace_back(center, region_.max());

            octant.emplace_back(lingeo::Vector{center.x(), region_.min().y(), region_.min().z()},
                                lingeo::Vector{region_.max().x(), center.y(), center.z()});

            octant.emplace_back(lingeo::Vector{center.x(), region_.min().y(), center.z()},
                                lingeo::Vector{region_.max().x(), center.y(), region_.max().z()});

            octant.emplace_back(lingeo::Vector{region_.min().x(), region_.min().y(), center.z()},  
                                lingeo::Vector{center.x(), center.y(), region_.max().z()});

            octant.emplace_back(lingeo::Vector{region_.min().x(), center.y(), region_.min().z()},  
                                lingeo::Vector{center.x(), region_.max().y(), center.z()});

            octant.emplace_back(lingeo::Vector{center.x(), center.y(), region_.min().z()},
                                lingeo::Vector{region_.max().x(), region_.max().y(), center.z()});

            octant.emplace_back(lingeo::Vector{region_.min().x(), center.y(), center.z()},
                                lingeo::Vector{center.x(), region_.max().y(), region_.max().z()});

            std::array<std::vector<lingeo::Shape>, 8> oct_array;

            std::vector<shapes_iter> del_list;

            for (shapes_iter it = objects_.begin(), ite = objects_.end(); it != ite; ++it)
            {
                if (it->get_min_vec() != it->get_max_vec())
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
                objects_.erase(obj);
            
            for (int a = 0; a < 8; a++)
            {
                if (!oct_array[a].empty())
                {
                    OctTree_t *new_tree = new OctTree_t{octant[a], oct_array[a].begin(), oct_array[a].end()};
                    child_node_[a] = new_tree; 
                    child_node_[a]->parent_ = this;

                    if (child_node_[a] != nullptr)
                        child_node_[a]->build_tree();
                }
            }
        }

        size_t check_intersection_btw_objs() const
        {
            size_t num_intersections = 0;

            if (objects_.size() > 1)
            {
                std::list<lingeo::Shape> tmp = objects_;
                while (tmp.size() > 0)
                {
                    for (shapes_iter it = tmp.begin(), ite = std::prev(tmp.end()); it != ite; ++it)
                    {
                        if (lingeo::triangles_intersection(ite->get_triangle(), it->get_triangle()))
                        {
                            num_intersections++;
                            ite->add_to_intersect_shapes(); 
                            it->add_to_intersect_shapes();
                        }
                    }
                    tmp.pop_back();
                }
            }

            return num_intersections;
        }

        
        size_t count_intersection(std::list<lingeo::Shape> &parent_objs)
        {
            size_t num_intersections = 0;

            for (auto p_obj : parent_objs)
            {
                for (auto l_obj : objects_)
                {
                    if(lingeo::triangles_intersection(l_obj.get_triangle(), p_obj.get_triangle()))
                    {
                        num_intersections++;
                        l_obj.add_to_intersect_shapes();
                        p_obj.add_to_intersect_shapes();
                    }
                }
            }

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