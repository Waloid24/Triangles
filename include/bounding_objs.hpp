#ifndef BOUNDING_OBJS_HPP
#define BOUNDING_OBJS_HPP

#include "vector.hpp"
#include "maths.hpp"


namespace lingeo {

    class Bounding_box {

    lingeo::Vector_3D max_;
    lingeo::Vector_3D min_;

    public:

        Bounding_box() = default;

        Bounding_box(const lingeo::Vector_3D &vec1, const lingeo::Vector_3D &vec2, bool are_ordered = false) {

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
                max_.change_values(x1, y1, z1);
                min_.change_values(x2, y2, z2);
            }
            else
            {
                max_.change_values(x2, y2, z2);
                min_.change_values(x1, y1, z1);
            }
        }

        void find_enclosing_cube()
        {
            lingeo::Vector_3D offset = lingeo::Vector_3D{0} - min_;
            min_ += offset;
            max_ += offset;

            long long largest_size = cmp::round(get_largest_size());

            for (int bit = 0; bit < 64; bit++)
            {
                if (largest_size == (1 << bit))
                {
                    max_.change_values(largest_size, largest_size, largest_size);

                    min_ -= offset;
                    max_ -= offset;
                    return;
                }
            }

            long long x = maths::find_largest_pow_of_two(largest_size);

            max_.change_values(x, x, x);
            min_ -= offset;
            max_ -= offset;
        }

        lingeo::Vector_3D max() const { return max_; }

        lingeo::Vector_3D min() const { return min_; }

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
};

} /*namespace lingeo*/

#endif