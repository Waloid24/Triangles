#ifndef TRIANGLES_2D
#define TRIANGLES_2D

#include "../primitives/triangle.hpp"

namespace lingeo {

    inline bool p1_belongs_R1(const Triangle &T1, const Triangle &T2)
    {
        if (position_2D(T2.r(), T2.p(), T1.q()) != Location_2D::LEFT)
        {
            if (position_2D(T2.r(), T1.p(), T1.q()) != Location_2D::LEFT)
            {
                if (position_2D(T1.p(), T2.p(), T1.q()) != Location_2D::LEFT)
                    return true;
                else
                {
                    return (position_2D(T1.p(), T2.p(), T1.r()) != Location_2D::LEFT &&
                            position_2D(T1.q(), T1.r(), T2.p()) != Location_2D::LEFT);
                }
            }
            else
                return false;
        }
        else
        {
            if (position_2D(T2.r(), T2.p(), T1.r()) != Location_2D::LEFT)
            {
                return (position_2D(T1.q(), T1.r(), T2.r()) != Location_2D::LEFT &&
                        position_2D(T1.p(), T2.p(), T1.r()) != Location_2D::LEFT);
            }
            else
                return false;
        }
    }

    inline bool p1_belongs_R2(const Triangle &T1, const Triangle &T2)
    {
        if (position_2D(T2.r(), T2.p(), T1.q()) != Location_2D::LEFT)
        {
            if (position_2D(T2.q(), T2.r(), T1.q()) != Location_2D::LEFT)
            {
                if (position_2D(T1.p(), T2.p(), T1.q()) != Location_2D::LEFT)
                {
                    return !(position_2D(T1.p(), T2.q(), T1.q()) == Location_2D::RIGHT);
                }
                else 
                {
                    return (position_2D(T1.p(), T2.p(), T1.r()) != Location_2D::LEFT &&
                            position_2D(T2.r(), T2.p(), T1.r()) != Location_2D::LEFT);
                }
            }
            else
            {
                if (position_2D(T1.p(), T2.q(), T1.q()) != Location_2D::RIGHT)
                {
                    return (position_2D(T2.q(), T2.r(), T1.r()) != Location_2D::LEFT &&
                            position_2D(T1.q(), T1.r(), T2.q()) != Location_2D::LEFT);
                }
                else
                    return false;
            }
        }
        else
        {
            if (position_2D(T2.r(), T2.p(), T1.r()) != Location_2D::LEFT)
            {
                if (position_2D(T1.q(), T1.r(), T2.r()) != Location_2D::LEFT)
                {
                    return position_2D(T1.r(), T1.p(), T2.p()) != Location_2D::LEFT;
                }
                else
                {
                    return (position_2D(T1.q(), T1.r(), T2.q()) != Location_2D::LEFT &&
                            position_2D(T2.q(), T2.r(), T1.r()) != Location_2D::LEFT);
                }
            }
            else
                return false;
        }
    }

    enum Plane {
        XY,
        XZ,
        YZ
    };

    Triangle project_onto_plane(const Triangle &tr, const Plane &projection_plane) //if error?
    {
        switch (projection_plane)
        {
            case Plane::YZ:
                return Triangle{Vector{tr.p().y(), tr.p().z(), 0},
                                Vector{tr.q().y(), tr.q().z(), 0},
                                Vector{tr.r().y(), tr.r().z(), 0}};
            
            case Plane::XZ:
                return Triangle{Vector{tr.p().z(), tr.p().x(), 0},
                                Vector{tr.q().z(), tr.q().x(), 0},
                                Vector{tr.r().z(), tr.r().x(), 0}};

            default:
                return Triangle{Vector{tr.p().x(), tr.p().y(), 0},
                                Vector{tr.q().x(), tr.q().y(), 0},
                                Vector{tr.r().x(), tr.r().y(), 0}};
        }
    }

    Plane projection_plane(const Triangle &T1)
    {
        if (position_2D(T1.p(), T1.q(), T1.r(), Z) == Location_2D::ON)
        {
            if (position_2D(T1.p(), T1.q(), T1.r(), Y) == Location_2D::ON)
                return YZ;
            else
                return XZ;
        }
        else
            return XY;
    }

    inline bool triangles_intersection_2D(Triangle &T1, Triangle &T2)
    {
        T1 = project_onto_plane(T1, projection_plane(T1));
        T2 = project_onto_plane(T2, projection_plane(T2));

        T1.arrange_counterclockwise();
        T2.arrange_counterclockwise();

        auto det_p2_q2_p1 = position_2D(T2.p(), T2.q(), T1.p());
        auto det_q2_r2_p1 = position_2D(T2.q(), T2.r(), T1.p());
        auto det_r2_p2_p1 = position_2D(T2.r(), T2.p(), T1.p());

        if (det_q2_r2_p1 == Location_2D::ON && det_r2_p2_p1 == Location_2D::ON 
                                            && det_p2_q2_p1 == Location_2D::ON)
            return false;
        else if (det_q2_r2_p1 == Location_2D::RIGHT && det_r2_p2_p1 == Location_2D::RIGHT 
                                                    && det_p2_q2_p1 == Location_2D::RIGHT)
            return true;
        else if (det_q2_r2_p1 == Location_2D::ON)
        {
            if (det_r2_p2_p1 == Location_2D::RIGHT && det_p2_q2_p1 == Location_2D::RIGHT)
                return true;
            else if (det_r2_p2_p1 == Location_2D::ON || det_p2_q2_p1 == Location_2D::ON)
                return true;
            else
                return false;
        }
        else if (det_r2_p2_p1 == Location_2D::ON)
        {
            if (det_q2_r2_p1 == Location_2D::RIGHT && det_p2_q2_p1 == Location_2D::RIGHT)
                return true;
            else if (det_q2_r2_p1 == Location_2D::ON || det_p2_q2_p1 == Location_2D::ON)
                return true;
            else
                return false;
        }
        else if (det_p2_q2_p1 == Location_2D::ON)
        {
            if (det_q2_r2_p1 == Location_2D::RIGHT && det_r2_p2_p1 == Location_2D::RIGHT)
                return true;
            else if (det_q2_r2_p1 == Location_2D::ON || det_r2_p2_p1 == Location_2D::ON)
                return true;
            else 
                return false;
        }

        for (int i = 0; i < 3; ++i)
        {
            if (det_p2_q2_p1 != Location_2D::LEFT   && det_q2_r2_p1 != Location_2D::RIGHT 
                                                    && det_r2_p2_p1 != Location_2D::RIGHT)
                return p1_belongs_R2(T1, T2);
            if (det_p2_q2_p1 == Location_2D::RIGHT  && det_q2_r2_p1 == Location_2D::RIGHT 
                                                    && det_r2_p2_p1 == Location_2D::LEFT)
                return p1_belongs_R1(T1, T2);

            T2.circular_permutation();

            det_p2_q2_p1 = position_2D(T2.p(), T2.q(), T1.p());
            det_q2_r2_p1 = position_2D(T2.q(), T2.r(), T1.p());
            det_r2_p2_p1 = position_2D(T2.r(), T2.p(), T1.p());
        }

        return false;
    }

}

#endif