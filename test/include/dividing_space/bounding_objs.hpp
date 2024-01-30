#ifndef BOUNDING_OBJS_HPP
#define BOUNDING_OBJS_HPP

#include "../maths/maths.hpp"

namespace lingeo {

class Bounding_box final {

    lingeo::Vector min_;
    lingeo::Vector max_;

    public:

        Bounding_box(const lingeo::Vector &vec1, const lingeo::Vector &vec2) : 
            min_{std::min(vec1, vec2, comparator_x).x(),
                    std::min(vec1, vec2, comparator_y).y(),
                    std::min(vec1, vec2, comparator_z).z()},
            max_{std::max(vec1, vec2, comparator_x).x(),
                    std::max(vec1, vec2, comparator_y).y(),
                    std::max(vec1, vec2, comparator_z).z()} {}

        Bounding_box(const Vector* it_begin, const Vector* it_end) : Bounding_box{
                Vector{ std::min_element(it_begin, it_end, comparator_x)->x(),
                        std::min_element(it_begin, it_end, comparator_y)->y(),
                        std::min_element(it_begin, it_end, comparator_z)->z()},
                Vector{ std::max_element(it_begin, it_end, comparator_x)->x(),
                        std::max_element(it_begin, it_end, comparator_y)->y(),
                        std::max_element(it_begin, it_end, comparator_z)->z()}} {}

        void find_border() 
        {
            lingeo::Vector offset = lingeo::Vector{0} - min_;
            min_ += offset;
            max_ += offset;

            long long largest_size = maths::round(get_largest_size());

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
        
        Vector max() const { return max_; }
        Vector min() const { return min_; }

        bool contains(const Bounding_box &obj) const
        {
            if ((max_ > obj.max()) && (min_ < obj.min()))
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

            return maths::max(size_z, maths::max(size_x, size_y)); 
        }

        static constexpr auto comparator_x = [](const Vector &v1, const Vector &v2)
        {
            return maths::less(v1.x(), v2.x());
        };

        static constexpr auto comparator_y = [](const Vector &v1, const Vector &v2)
        {
            return maths::less(v1.y(), v2.y());
        };

        static constexpr auto comparator_z = [](const Vector &v1, const Vector &v2)
        {
            return maths::less(v1.z(), v2.z());
        };
};

} /* namespace lingeo */

#endif