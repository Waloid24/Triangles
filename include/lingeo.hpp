#ifndef LINGEO_HPP
#define LINGEO_HPP

#include <iostream>
#include <cmath>

namespace lingeo {

    enum PLANES {
        YZ = 0,
        XZ = 1,
        XY = 2
    };

    enum AXES {
        X = 0,
        Y = 1,
        Z = 2
    };

    enum Positions {
        DOESNT_INTERSECT = 0,
        INTERSECT = 1,
        COMPLANAR = 2
    };

    class Point_t {

        double x_= NAN, y_ = NAN, z_ = NAN;

        public:

            Point_t(double x, double y, double z) : x_{x}, y_{y}, z_{z} {};

            void print() const { std::cout << "(" << x_ << " ; " << y_ << " ; " << z_ << ")" << std::endl; }
            
            int valid() const { 
                if (std::isnan(x_) || std::isnan(y_) || std::isnan(z_)) 
                    return 0;
                else
                    return 1;
            }

            void project_onto_plane(int plane = XY)
            {
                if (plane == XY)
                {
                    return;
                }
                else if (plane == XZ)
                {
                    y_ = z_;
                    z_ = 1;
                }
                else
                {
                    x_ = y_;
                    y_ = z_;
                    z_ = 1;
                }
                return;
            }

            double x() { return x_; }
            double y() { return y_; }
            double z() { return z_; }
    };

    double det_abcd(Point_t a, Point_t b, Point_t c, Point_t d)
    {
        if (a.valid() && b.valid() && c.valid())
        {
            return  a.x()*(b.y()*(c.z() - d.z()) - b.z()*(c.y() - d.y()) + c.y()*d.z() - d.y()*c.z()) - 
                    a.y()*(b.x()*(c.z() - d.z()) - b.z()*(c.x() - d.x()) + c.x()*d.z() - d.x()*c.z()) +
                    a.z()*(b.x()*(c.y() - d.y()) - b.y()*(c.x() - d.x()) + c.x()*d.y() - d.x()*c.y()) -
                    1    *(b.x()*(c.y()*d.z() - d.y()*c.z()) - b.y()*(c.x()*d.z() - d.x()*c.z()) + b.z()*(c.x()*d.y() - d.x()*c.y()));
        }
        else
        {
            return NAN;
        }
    }

    double det_abc(Point_t a, Point_t b, Point_t c, int axis = Z)
    {
        if (a.valid() && b.valid() && c.valid())
        {
            if (axis = Z)
                return a.x()*(b.y() - c.y()) - a.y()*(b.x() - c.x()) + b.x()*c.y() - c.x()*b.y();
            else if (axis = Y)
                return a.x()*(c.z() - b.z()) - (b.x()*c.z() - c.x()*b.z()) + a.z()*(b.x() - c.x());
            else 
                return b.y()*c.z() - c.y()*b.z() - a.y()*(c.z() - b.z()) + a.z()*(c.y() - b.y());
        }
        else
        {
            return NAN;
        }
    }

    class Triangle_t {

        Point_t p_, q_, r_;

        public:

            Triangle_t(std::vector<double> coords) : p_{coords[0], coords[1], coords[2]}, q_{coords[3], coords[4], coords[5]}, 
                                                    r_{coords[6], coords[7], coords[8]} {}

            void print() const { 
                std::cout << "p";
                p_.print();
                std::cout << std::endl;

                std::cout << "q";
                q_.print();
                std::cout << std::endl;

                std::cout << "r";
                r_.print();
                std::cout << std::endl;
            }

            void project_onto_plane()
            {
                if (det_abc(p_, q_, r_, Z) == 0)
                {
                    std::cout << "Projecting onto the Oxy = 0" << std::endl;
                    if (det_abc(p_, q_, r_, Y) == 0)
                    {
                        std::cout << "Projecting onto the Oxz = 0. Project onto the Oyz" << std::endl;

                        p_.project_onto_plane(YZ);
                        q_.project_onto_plane(YZ);
                        r_.project_onto_plane(YZ);
                    }
                    else //if (det_abc(T.p(), T.q(), T.r(), X) == 0)
                    {
                        std::cout << "Projecting onto the Oxz" << std::endl;
                        
                        p_.project_onto_plane(XZ);
                        q_.project_onto_plane(XZ);
                        r_.project_onto_plane(XZ);
                    }
                }
                else
                {
                    std::cout << "Project onto Oxy" << std::endl;
                    
                    p_.project_onto_plane(XY);
                    q_.project_onto_plane(XY);
                    r_.project_onto_plane(XY);
                }
            }

            void swap_two_points()
            {
                Point_t temp_q = q_;
                q_ = r_;
                r_ = temp_q;
            }

            void arrange_counterclockwise()
            {
                std::cout << "det_abc(p,q,r) = " << det_abc(p_, q_, r_) << std::endl;

                if (det_abc(p_, q_, r_) < 0)
                {
                    swap_two_points();
                    std::cout << "det_abc adter swap_two_points() = " << det_abc(p_, q_, r_) << std::endl;

                }
            }
            
            void circular_permutation()
            {
                Point_t temp_r = r_;
                Point_t temp_q = q_;
                q_ = p_;
                r_ = temp_q;
                p_ = temp_r;
            }

            Point_t p() { return p_; }
            Point_t q() { return q_; }
            Point_t r() { return r_; }

    };    

    enum Positions intersection_of_triangle_and_plane(Triangle_t T1, Triangle_t T2) 
    {
        double p2_q2_r2_p1 = det_abcd(T2.p(), T2.q(), T2.r(), T1.p());
        double p2_q2_r2_q1 = det_abcd(T2.p(), T2.q(), T2.r(), T1.q());
        double p2_q2_r2_r1 = det_abcd(T2.p(), T2.q(), T2.r(), T1.r());

        if (!std::isnan(p2_q2_r2_p1) && !std::isnan(p2_q2_r2_q1) != NAN && !std::isnan(p2_q2_r2_r1) != NAN)
        {
            if ((p2_q2_r2_p1 > 0 && p2_q2_r2_q1 > 0 && p2_q2_r2_r1 > 0) ||
                (p2_q2_r2_p1 < 0 && p2_q2_r2_q1 < 0 && p2_q2_r2_r1 < 0))
            {
                std::cout << "triangle and plane: DOESNT_INTERSECT" << std::endl;
                return DOESNT_INTERSECT;
            }
            else if (p2_q2_r2_p1 == 0 && p2_q2_r2_q1 == 0 && p2_q2_r2_r1 == 0)
            {
                std::cout << "triangle and plane: COMPLANAR" << std::endl;
                return COMPLANAR;
            }
            else 
            {
                std::cout << "triangle and plane: INTERSECT" << std::endl;
                return INTERSECT;
            }
        }
        else 
        {
            std::cout << "is_nan: DOESNT_INTERSECT" << std::endl;
            return DOESNT_INTERSECT;
        }
    }

    template<typename T> int sgn(T val)
    {
        return (T(0) < val) - (val < T(0));
    }

    int arrange_3D_triangle_points(Triangle_t T1, Triangle_t T2)
    {
        std::cout << "Before arranging" << std::endl;
        T1.print();
        T2.print();

        int det_p = det_abcd(T2.p(), T2.q(), T2.r(), T1.p()); //TODO: I need only sign of this expression. Merge 'sgn()' and 'det()'
        int det_q = det_abcd(T2.p(), T2.q(), T2.r(), T1.q());
        int det_r = det_abcd(T2.p(), T2.q(), T2.r(), T1.r());

        std::cout << "before arranging" << std::endl;

        std::cout << "det_p = " << det_p << std::endl;
        std::cout << "det_q = " << det_q << std::endl;
        std::cout << "det_r = " << det_r << std::endl;

        if (det_p == 0 && det_q == 0 && det_r == 0)
        {
            return -1;
        }
        for (int i = 0; i < 3; ++i)
        {
            std::cout << "i = " << i << std::endl;
            if ( (sgn<int>(det_q) == sgn<int>(det_r)) && (sgn<int>(det_p) != sgn<int>(det_q)) ) // by construction, the last check can be removed
            {
                if (sgn<int>(det_p) < 0)
                {
                    T2.swap_two_points();
                    break;
                }
                else if (sgn<int>(det_p) == 0 && sgn<int>(det_q) > 0)
                {
                    T2.swap_two_points();
                }
                break;
            }
            else
            {
                T1.circular_permutation();
            }
            det_p = det_abcd(T2.p(), T2.q(), T2.r(), T1.p()); //TODO: I need only sign of this expression. Merge 'sgn()' and 'det()'
            det_q = det_abcd(T2.p(), T2.q(), T2.r(), T1.q());
            det_r = det_abcd(T2.p(), T2.q(), T2.r(), T1.r());

            // std::cout << "det_p = " << det_p << std::endl;
            // std::cout << "det_q = " << det_q << std::endl;
            // std::cout << "det_r = " << det_r << std::endl;
        }

        det_p = det_abcd(T2.p(), T2.q(), T2.r(), T1.p()); //TODO: only for checking below. Must be removed later
        det_q = det_abcd(T2.p(), T2.q(), T2.r(), T1.q());
        det_r = det_abcd(T2.p(), T2.q(), T2.r(), T1.r());

        

        if ( ((sgn<int>(det_q) == sgn<int>(det_r) && sgn<int>(det_r) <= 0 && sgn<int>(det_p) >  0)) || 
             ((sgn<int>(det_q) < 0 && sgn<int>(det_r) < 0 && sgn<int>(det_p) == 0)) )
        {
            std::cout << "\033[36;1m Successful arranging\033[0m" << std::endl;

            T1.print();
            T2.print();

            return 1;
        }
        else
        {
            std::cout << "\033[31;1m Unsuccessful arranging\033[0m" << std::endl;

            T1.print();
            T2.print();
            
            return 0;
        }

        T1.print();
        T2.print();

        return -1;
    }

    int check_3D_triangles_intersection(Triangle_t T1, Triangle_t T2)
    {

        int res1 = arrange_3D_triangle_points(T1, T2);
        if (res1 == 1)
        {
            std::cout << "T1 is sorted relative to T2" << std::endl;
        }
        else if (res1 == 0)
        {
            std::cout << "It was not possible to arrange T1 relative to T2" << std::endl;
        }
        else
        {
            std::cout << "Some error when ordering T1 relative to T2" << std::endl;
        }


        // int res2 = arrange_3D_triangle_points(T2, T1);
        // if (res2 == 1)
        // {
        //     std::cout << "T2 is sorted relative to T1" << std::endl;
        // }
        // else if (res2 == 0)
        // {
        //     std::cout << "It was not possible to arrange T2 relative to T1" << std::endl;
        // }
        // else
        // {
        //     std::cout << "Some error when ordering T2 relative to T1" << std::endl;
        // } 

        if (det_abcd(T1.p(), T1.q(), T2.p(), T2.q()) <= 0 && det_abcd(T1.p(), T1.r(), T2.r(), T2.p()) <= 0)
        {
            return INTERSECT;
        }

        return DOESNT_INTERSECT; //MUST BE CHANGED
    }

    int p1_belongs_R1(Triangle_t T1, Triangle_t T2)
    {
        if (det_abc(T2.r(), T2.p(), T1.q()) >= 0)
        {
            if (det_abc(T2.r(), T1.p(), T1.q()) >= 0)
            {
                if (det_abc(T1.p(), T2.p(), T1.q()) >= 0)
                    return DOESNT_INTERSECT;
                else
                {
                    if (det_abc(T1.p(), T2.p(), T1.r()) >= 0)
                    {
                        if (det_abc(T1.q(), T1.r(), T2.p()) >= 0)
                            return INTERSECT;
                        else
                            return DOESNT_INTERSECT;
                    }
                    else
                        return DOESNT_INTERSECT;
                }
            }
            else
                return DOESNT_INTERSECT;
        }
        else
        {
            if (det_abc(T2.r(), T2.p(), T1.r()) >= 0)
            {
                if (det_abc(T1.q(), T1.r(), T2.r()) >= 0)
                {
                    if (det_abc(T1.p(), T2.p(), T1.r()) >= 0)
                        return INTERSECT;
                    else
                        return DOESNT_INTERSECT;
                }
                else
                    return DOESNT_INTERSECT;
            }
            else
                return DOESNT_INTERSECT;
        }
    }

    int p1_belongs_R2(Triangle_t T1, Triangle_t T2)
    {
        if (det_abc(T2.r(), T2.p(), T1.q()) >= 0)
        {
            if (det_abc(T2.q(), T2.r(), T1.q()) >= 0)
            {
                if (det_abc(T1.p(), T2.p(), T1.q()) >= 0)
                {
                    if (det_abc(T1.p(), T2.q(), T1.q()) > 0)
                        return DOESNT_INTERSECT;
                    else
                        return INTERSECT;
                }
                else 
                {
                    if (det_abc(T1.p(), T2.p(), T1.r()) >= 0)
                    {
                        if (det_abc(T2.r(), T2.p(), T1.r()) >= 0)
                            return INTERSECT;
                        else
                            return DOESNT_INTERSECT;
                    }
                    else
                        return DOESNT_INTERSECT;
                }
            }
            else
            {
                if (det_abc(T1.p(), T2.q(), T1.q()) <= 0)
                {
                    if (det_abc(T2.q(), T2.r(), T1.r()) >= 0)
                    {
                        if (det_abc(T1.q(), T1.r(), T2.q()) >= 0)
                            return INTERSECT;
                        else
                            return DOESNT_INTERSECT;
                    }
                    else
                        return DOESNT_INTERSECT;
                }
                else
                    return DOESNT_INTERSECT;
            }
        }
        else
        {
            if (det_abc(T2.r(), T2.p(), T1.r()) >= 0)
            {
                if (det_abc(T1.q(), T1.r(), T2.r()) >= 0)
                {
                    if (det_abc(T1.r(), T1.p(), T2.p()) >= 0)
                        return INTERSECT;
                    else
                        return DOESNT_INTERSECT;
                }
                else
                {
                    if (det_abc(T1.q(), T1.r(), T2.q()) >= 0)
                    {
                        if (det_abc(T2.q(), T2.r(), T1.r()) >= 0)
                            return INTERSECT;
                        else
                            return DOESNT_INTERSECT;
                    }
                    else
                        return DOESNT_INTERSECT;
                }
            }
            else
                return DOESNT_INTERSECT;
        }
    }

    int check_2D_triangles_intersection(Triangle_t T1, Triangle_t T2)
    {
        std::cout << "Before projecting" << std::endl;
        T1.print();
        T2.print();

        T1.project_onto_plane();
        T2.project_onto_plane();

        std::cout << "After projecting" << std::endl;
        T1.print();
        T2.print();

        T1.arrange_counterclockwise();
        T2.arrange_counterclockwise();

        std::cout << "After arranging" << std::endl;
        T1.print();
        T2.print();

        double det_p2_q2_p1 = det_abc(T2.p(), T2.q(), T1.p());
        double det_q2_r2_p1 = det_abc(T2.q(), T2.r(), T1.p());
        double det_r2_p2_p1 = det_abc(T2.r(), T2.p(), T1.p());

        std::cout << "det_p2_q2_p1 = " << det_p2_q2_p1 << std::endl;
        std::cout << "det_q2_r2_p1 = " << det_q2_r2_p1 << std::endl;
        std::cout << "det_r2_p2_p1 = " << det_r2_p2_p1 << "\n" << std::endl;

        if (det_q2_r2_p1 == 0 && det_r2_p2_p1 == 0 && det_p2_q2_p1 == 0)
        {
            return DOESNT_INTERSECT;
        }
        else if (det_q2_r2_p1 > 0 && det_r2_p2_p1 > 0 && det_p2_q2_p1 > 0)
        {
            return INTERSECT;
        }
        else if (det_q2_r2_p1 == 0)
        {
            if (det_r2_p2_p1 > 0 && det_p2_q2_p1 > 0)
                return INTERSECT;
            else if (det_r2_p2_p1 == 0)
                return INTERSECT;
            else if (det_p2_q2_p1 == 0)
                return INTERSECT;
            else
                return DOESNT_INTERSECT;
        }
        else if (det_r2_p2_p1 == 0)
        {
            if (det_q2_r2_p1 > 0 && det_p2_q2_p1 > 0)
                return INTERSECT;
            else if (det_q2_r2_p1 == 0)
                return INTERSECT;
            else if (det_p2_q2_p1 == 0)
                return INTERSECT;
            else
                return DOESNT_INTERSECT;
        }
        else if (det_p2_q2_p1 == 0)
        {
            if (det_q2_r2_p1 > 0 && det_r2_p2_p1 > 0)
                return INTERSECT;
            else if (det_q2_r2_p1 == 0)
                return INTERSECT;
            else if (det_r2_p2_p1 == 0)
                return INTERSECT;
            else 
                return DOESNT_INTERSECT;
        }

        
        for (int i = 0; i < 3; ++i)
        {
            if (det_p2_q2_p1 > 0 && det_q2_r2_p1 < 0 && det_r2_p2_p1 < 0)
            {
                std::cout << "p1_belongs_R2" << std::endl;
                return p1_belongs_R2(T1, T2);
            }
            if (det_p2_q2_p1 > 0 && det_q2_r2_p1 > 0 && det_r2_p2_p1 < 0)
            {
                std::cout << "p1_belongs_R1" << std::endl;
                return p1_belongs_R1(T1, T2);
            }
            T2.circular_permutation();

            det_p2_q2_p1 = det_abc(T2.p(), T2.q(), T1.p());
            det_q2_r2_p1 = det_abc(T2.q(), T2.r(), T1.p());
            det_r2_p2_p1 = det_abc(T2.r(), T2.p(), T1.p());

            std::cout << "det_p2_q2_p1 = " << det_p2_q2_p1 << std::endl;
            std::cout << "det_q2_r2_p1 = " << det_q2_r2_p1 << std::endl;
            std::cout << "det_r2_p2_p1 = " << det_r2_p2_p1 << "\n" << std::endl;
        }

        return DOESNT_INTERSECT;
    }


    int intersection_3D_triangles(Triangle_t T1, Triangle_t T2)
    {
        int result1 = intersection_of_triangle_and_plane(T1, T2);
        int result2 = intersection_of_triangle_and_plane(T2, T1);

        if (result1 == INTERSECT && result2 == INTERSECT)
        {
            return check_3D_triangles_intersection(T1, T2);
        }
        else if (result1 == COMPLANAR && result2 == COMPLANAR)
        {
            return check_2D_triangles_intersection(T1, T2);
        }
        else
        {
            return DOESNT_INTERSECT;
        }
    }



}

#endif