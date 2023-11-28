#ifndef BOUNDING_OBJS_HPP
#define BOUNDING_OBJS_HPP

#include "vector.hpp"


namespace lingeo {

    class Bounding_box {

    lingeo::Vector3 max_;
    lingeo::Vector3 min_;

    public:

        Bounding_box() = default;

        Bounding_box(lingeo::Vector3 vec1, lingeo::Vector3 vec2, bool are_ordered = false) {

            if (!are_ordered)
            {
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
            else
            {
                max_ = vec2;
                min_ = vec1;
            }
        }

        Bounding_box(double x1, double y1, double z1, double x2, double y2, double z2)
        {
            if (cmp::greater(x1, x2) && cmp::greater(y1, y2) && cmp::greater(z1, z2))
            {
                lingeo::Vector3 tmp1{x1, y1, z1};
                lingeo::Vector3 tmp2{x2, y2, z2};
                
                max_ = tmp1; //TODO: very ugly
                min_ = tmp2; //TODO: very ugly
            }
            else
            {
                lingeo::Vector3 tmp1{x1, y1, z1};
                lingeo::Vector3 tmp2{x2, y2, z2};

                max_ = tmp2; //TODO: very ugly
                min_ = tmp1; //TODO: very ugly
            }
        }

        void find_enclosing_cube()
        {
            lingeo::Vector3 offset = lingeo::Vector3{0} - min_;
            min_ += offset;
            max_ += offset;

            int largest_size = cmp::round(get_largest_size());

            for (int bit = 0; bit < 32; bit++)
            {
                if (largest_size == (1 << bit))
                {
                    max_.change_values(largest_size, largest_size, largest_size);

                    min_ -= offset;
                    max_ -= offset;
                    return;
                }
            }

            int x = find_highest_pow_two(largest_size);

            max_.change_values(x, x, x);
            min_ -= offset;
            max_ -= offset;
        }

        lingeo::Vector3 max() const { return max_; }

        lingeo::Vector3 min() const { return min_; }

        bool contains(Bounding_box box) const
        {
            if ((max_ > box.max()) && (min_ < box.min()))
                return true;
            else
                return false;   
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

} /*namespace lingeo*/

#endif