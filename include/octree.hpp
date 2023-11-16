#ifndef OCTREE_HPP
#define OCTREE_HPP

#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <array>
#include "vector.hpp"

//TODO: the bounding boxes are a power of two - an integer. Do it.

namespace octree {

class Bounding_box {

    lingeo::Vector3 max_;
    lingeo::Vector3 min_;

    public:

        Bounding_box(lingeo::Vector3 vec1, lingeo::Vector3 vec2) {

            if (vec1 >= vec2)
            {
                max_ = vec1;
                min_ = vec2;
            }
            else
            {
                max_ = vec2;
                min_ = vec1;
            }
        }

        lingeo::Vector3 max() const
            return max_;

        lingeo::Vector3 min() const
            return min_;

        void find_enclosing_cube ()
        {
            lingeo::Vector3 offset = lingeo::Vector3{0, 0, 0} - min_;
            min_ += offset;
            max_ += offset;

            int largest_size = cmp::round(get_largest_size());

            for (int bit = 0; bit < 32; bit++)
            {
                if (largest_size == (1 << bit)) //TODO: is it the correct to compare this way?
                {
                    max_{largest_size, largest_size, largest_size}; //TODO: is memory leaking?

                    min_ -= offset;
                    max_ -= offset;
                    return;
                }
            }

            int x = find_highest_pow_two(largest_size);

            max_{x, x, x}; //TODO: is memory leaking?
            min_ -= offset;
            max_ -= offset;
        }

    private:

        double get_largest_size()
        {
            double size_x = max_.x() - min_.x();
            double size_y = max_.y() - min_.y();
            double size_z = max_.z() - min_.z();

            return cmp::max(size_z, cmp::max(size_x, size_y)); 
        }

        int find_highest_pow_two(int num)
        {
            num--;
            num |= num >> 1;
            num |= num >> 2;
            num |= num >> 4;
            num |= num >> 8;
            num |= num >> 16;
            num++;
            return num;
        }
};

class OctTree_t {
    
    std::list<lingeo::Triangle_t> objects_;

    std::vector<OctTree_t *> child_node;

    const int MIN_SIZE = 1;

    OctTree_t *parent_;

    Bounding_box region_;

    std::queue<lingeo::Triangle_t> pendingInsertion;

    bool is_tree_built = false;
    bool is_tree_ready = false;


    using tr_vec_it = typename std::vector<lingeo::Triangle_t>::iterator;
    using tr_list_it = typename std::list<lingeo::Triangle_t>::iterator;

    public:

        OctTree_t(Bounding_box region, tr_vec_it &begin, tr_vec_it &end) : region_{region} {

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

            if (dimensions == lingeo::Vector3{0, 0, 0})
            {
                find_enclosing_cube();
                dimensions = region_.max() - region_.min();
            }

            if (dimensions.x <= MIN_SIZE && dimensions.y <= MIN_SIZE && dimensions.z <= MIN_SIZE)
            {
                return;
            }

            lingeo::Vector3 half = dimensions / 2.0f;
            lingeo::Vector3 center = region_.min() + half;

            std::vector<Bounding_box> octant;
            octant.emplace_back(region_.min(), center);
            octant.emplace_back(lingeo::Vector3(center.x(), region_.min().y(), region_.min().z()),    lingeo::Vector3(region_.max().x(), center.y(), center.z()));
            octant.emplace_back(lingeo::Vector3(center.x(), region_.min().y(), center.z()),           lingeo::Vector3(region_.max().x(), center.y(), region_.max().z()));
            octant.emplace_back(lingeo::Vector3(region_.min().x(), region_.min().y(), center.z()),  lingeo::Vector3(center.x(), center.y(), region_.max().z()));
            octant.emplace_back(lingeo::Vector3(region_.min().x(), center.y(), region_.min().z()),  lingeo::Vector3(center.x(), region_.max().y(), center.z()));
            octant.emplace_back(lingeo::Vector3(center.x(), center.y(), region_.min().z()),         lingeo::Vector3(region_.max().x(), region_.max().y(), center.z()));
            octant.emplace_back(center, region_.max());
            octant.emplace_back(lingeo::Vector3(region_.min().x(), center.y(), center.z()),         lingeo::Vector3(center.x(), region_.max().y(), region_.max().z()));

            std::array<std::list<lingeo::Triangle_t>, 8> oct_list{};

            std::vector<tr_vec_it> del_list;

            for (tr_list_it it = objects_.begin(), ite = objects_.end(); it != ite; ++it)
            {
                if (obj.Bounding_box.min != obj.Bounding_box.max)
                {
                    for (int a = 0; a < 8; ++a)
                    {
                        if (octant[a].contains(obj.Bounding_box))
                        {
                            oct_list[a].push_back(*it);
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
                if (!oct_list[a].empty())
                {
                    child_node[a] = create_node(octant[a], oct_list[a]);
                    if (child_node[a] != nullptr)
                    {
                        child_node[a]->build_tree();
                    }
                }
            }

            is_tree_built = true;
            is_tree_ready = true;
        }

        OctTree_t *create_node(Bounding_box region, std::list<lingeo::Triangle_t> &objects)
        {
            if (!objects.empty())
                return nullptr;
            
            OctTree_t *ret = new OctTree_t(region, objects.begin(), objects.end());
            ret->parent_ = this;

            return ret;   
        }
};

} /* namespace octree */


#endif