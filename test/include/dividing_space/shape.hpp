#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "../primitives/triangle.hpp"
#include "bounding_objs.hpp"

namespace lingeo {

class Shape final {

    Triangle tr_;
    Bounding_box b_obj_;

    public:
        Shape(Triangle &tr) : tr_{tr}, b_obj_{tr.begin(), tr.end()} {}

        Vector get_min_vec() const
        {
            return b_obj_.min();
        }

        Vector get_max_vec() const
        {
            return b_obj_.max();
        }

        const Bounding_box& get_bounding_box() const 
        {
            return b_obj_;
        }

        Triangle get_triangle() const
        {
            return tr_;
        }

        void add_to_intersect_shapes()
        {
            tr_.add_to_intersect_triangles();
        }

        Triangle get_triangle()
        {
            return tr_;
        }
};

}


#endif