#ifndef TRIANGLES_INTERSECTION_HPP
#define TRIANGLES_INTERSECTION_HPP

#include "../primitives/triangle.hpp"
#include "triangles_3D.hpp"
#include "triangles_2D.hpp"

namespace lingeo {

    inline bool triangles_intersection(Triangle T1, Triangle T2)
    {
        Triangle_Position result1 = triangle_and_plane_intersection(T1, T2);
        Triangle_Position result2 = triangle_and_plane_intersection(T2, T1);

        if (result1 == Triangle_Position::INTERSECT && result2 == Triangle_Position::INTERSECT)
            return triangles_intersection_3D(T1, T2);
        else if (result1 == Triangle_Position::COPLANAR && result2 == Triangle_Position::COPLANAR)
            return triangles_intersection_2D(T1, T2);
        else
            return false;
    }

} /* namespace lingeo */

#endif