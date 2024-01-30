#ifndef TRIANGLES_3D
#define TRIANGLES_3D

namespace lingeo {

enum class Triangle_Position
{
    DOESNT_INTERSECT,
    COPLANAR,
    INTERSECT
};

inline std::tuple<Location_3D, Location_3D, Location_3D> get_rel_location(const Triangle &T1, const Triangle &T2)
{
    Location_3D pos_P = position_3D(T2.p(), T2.q(), T2.r(), T1.p());
    Location_3D pos_Q = position_3D(T2.p(), T2.q(), T2.r(), T1.q());
    Location_3D pos_R = position_3D(T2.p(), T2.q(), T2.r(), T1.r());

    return std::tuple{pos_P, pos_Q, pos_R};
}

inline Triangle_Position triangle_and_plane_intersection(const Triangle &T1, const Triangle &T2) 
{
    auto [P1_loc, Q1_loc, R1_loc] = get_rel_location(T1, T2);

    if ((P1_loc == Location_3D::ABOVE && Q1_loc == Location_3D::ABOVE && R1_loc == Location_3D::ABOVE) ||
        (P1_loc == Location_3D::BELOW && Q1_loc == Location_3D::BELOW && R1_loc == Location_3D::BELOW))
    {
        return Triangle_Position::DOESNT_INTERSECT;
    }
    else if (P1_loc == Location_3D::ON && Q1_loc == Location_3D::ON && R1_loc == Location_3D::ON)
    {
        return Triangle_Position::COPLANAR;
    }
    else 
    {
        return Triangle_Position::INTERSECT;
    }
}

inline void arrange_triangles_3D(Triangle &T1, Location_3D P1_loc, Location_3D Q1_loc, Location_3D R1_loc,
                                    Triangle &T2)
{
    switch (P1_loc)
    {
        case Location_3D::ABOVE:
        
            if (Q1_loc == Location_3D::ABOVE && R1_loc != Location_3D::ABOVE)
            {
                T1.swap_clockwise();
                T2.swap_q_r();
            }
            else if (Q1_loc != Location_3D::ABOVE && R1_loc == Location_3D::ABOVE)
            {
                T1.swap_counterclockwise();
                T2.swap_q_r();
            }
            break;

        case Location_3D::ON:

            if (Q1_loc == Location_3D::ABOVE)
            {
                if (R1_loc == Location_3D::ABOVE)
                    T2.swap_q_r();
                else
                    T1.swap_counterclockwise();
            }
            else if (R1_loc == Location_3D::ABOVE)
                T1.swap_clockwise();
            else if (Q1_loc == Location_3D::ON && R1_loc == Location_3D::BELOW)
            {
                T1.swap_clockwise();
                T2.swap_q_r();
            }
            else if (Q1_loc == Location_3D::BELOW && R1_loc == Location_3D::ON)
            {
                T1.swap_counterclockwise();
                T2.swap_q_r();
            }
            break;

        case Location_3D::BELOW:

            if (Q1_loc == R1_loc)
                T2.swap_q_r();
            else if (Q1_loc == Location_3D::BELOW)
                T1.swap_clockwise();
            else if (R1_loc == Location_3D::BELOW)
                T1.swap_counterclockwise();
            else
                T2.swap_q_r();
            break;
    }
}

inline bool triangles_intersection_3D(Triangle &T1, Triangle &T2)
{
    auto [P1_loc, Q1_loc, R1_loc] = get_rel_location(T1, T2);
    auto [P2_loc, Q2_loc, R2_loc] = get_rel_location(T2, T1);

    arrange_triangles_3D(T1, P1_loc, Q1_loc, R1_loc, T2);

    P1_loc = position_3D(T2.p(), T2.q(), T2.r(), T1.p());
    Q2_loc = position_3D(T1.p(), T1.q(), T1.r(), T2.q());
    R2_loc = position_3D(T1.p(), T1.q(), T1.r(), T2.r());

    arrange_triangles_3D(T2, P2_loc, Q2_loc, R2_loc, T1);

    P2_loc = position_3D(T1.p(), T1.q(), T1.r(), T2.p());

    if (P1_loc == Location_3D::ON && P2_loc == Location_3D::ON)
        return (T1.p() == T2.p());
    else
    {
        auto KJ_mut_pos = position_3D(T1.p(), T1.q(), T2.p(), T2.q());
        auto LI_mut_pos = position_3D(T1.p(), T1.r(), T2.p(), T2.r());
        return (KJ_mut_pos != Location_3D::ABOVE && LI_mut_pos != Location_3D::BELOW);
    }
}

} /* namespace lingeo */
    

#endif