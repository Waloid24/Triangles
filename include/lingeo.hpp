#ifndef LINGEO_HPP
#define LINGEO_HPP

#include <iostream>
#include <cmath>
#include <vector>
#include "double_comparison.hpp"

//TODO: add segment and degenerate cases - they are correct cases
//TODO: one defenition row (на cppreference), 3-d Vladimirov lection. Функции, которые в хэдере должны быть inline! Например, подключение в разные cpp'ки один hpp, на этапе линковки свалится. Если же
// inline, то можно несколько одинаковых с точки зрения лексического разбора функций написать. Там определение будет одно для нескольких единиц трансляции

namespace lingeo {

    typedef enum Axes {
        X,
        Y,
        Z
    } Axes;

    typedef enum Positions {
        DOESNT_INTERSECT,
        INTERSECT,
        COPLANAR
    } Positions;

    class Point_t final {

        double x_= NAN, y_ = NAN, z_ = NAN;

        public:

            Point_t(double x, double y, double z) : x_{x}, y_{y}, z_{z} {};

            void print() const { std::cout << "(" << x_ << " ; " << y_ << " ; " << z_ << ")" << std::endl; }
            
            int valid() const { 
                return !(std::isnan(x_) || std::isnan(y_) || std::isnan(z_));
            }

            void project_onto_XY()
            {
                std::exchange(z_, 0);
            }

            void project_onto_XZ()
            {
                std::exchange(y_, x_);
                std::exchange(x_, z_);
                std::exchange(z_, 0);
            }
            
            void project_onto_YZ()
            {
                std::exchange(x_, y_);
                std::exchange(y_, z_);
                std::exchange(z_, 0);
            }

            double x() const { return x_; }
            double y() const { return y_; }
            double z() const { return z_; }
    };

    double det(const Point_t &a, const Point_t &b, const Point_t &c, const Point_t &d)
    {
        if (a.valid() && b.valid() && c.valid())
        {
            return  (a.x()-d.x())*( (b.y()-d.y())*(c.z()-d.z()) - (c.y()-d.y())*(b.z()-d.z()) ) -
                    (a.y()-d.y())*( (b.x()-d.x())*(c.z()-d.z()) - (c.x()-d.x())*(b.z()-d.z()) ) +
                    (a.z()-d.z())*( (b.x()-d.x())*(c.y()-d.y()) - (b.y()-d.y())*(c.x()-d.x()) );
        }
        else
        {
            return NAN;
        }
    }

    double det(const Point_t &a, const Point_t &b, const Point_t &c, Axes axis = Z)
    {
        if (a.valid() && b.valid() && c.valid())
        {
            if (axis == Z)
                return a.x()*(b.y() - c.y()) - a.y()*(b.x() - c.x()) + b.x()*c.y() - c.x()*b.y();
            else if (axis == Y)
                return a.x()*(c.z() - b.z()) - (b.x()*c.z() - c.x()*b.z()) + a.z()*(b.x() - c.x());
            else 
                return b.y()*c.z() - c.y()*b.z() - a.y()*(c.z() - b.z()) + a.z()*(c.y() - b.y());
        }
        else
        {
            return NAN;
        }
    }

    class Triangle_t final {

        Point_t p_, q_, r_;

        public:

            Triangle_t(const std::vector<double> &coords) : p_{coords[0], coords[1], coords[2]}, q_{coords[3], coords[4], coords[5]}, 
                                                    r_{coords[6], coords[7], coords[8]} {} // receive three Point_t

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
                if (cmp::is_0(det(p_, q_, r_, Z)))
                {
                    if (cmp::is_0(det(p_, q_, r_, Y)))
                    {
                        p_.project_onto_YZ();
                        q_.project_onto_YZ();
                        r_.project_onto_YZ();
                    }
                    else
                    {                        
                        p_.project_onto_XZ();
                        q_.project_onto_XZ();
                        r_.project_onto_XZ();
                    }
                }
                else
                {                    
                    p_.project_onto_XY();
                    q_.project_onto_XY();
                    r_.project_onto_XY();
                }
            }

            void swap_q_r()
            {
                std::swap(q_, r_);
            }

            void arrange_counterclockwise()
            {
                if (cmp::less(det(p_, q_, r_),0))
                {
                    swap_q_r();
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

            Point_t p() const { return p_; }
            Point_t q() const { return q_; } // output using reference!
            Point_t r() const { return r_; }

    };

    Positions intersection_of_triangle_and_plane(Triangle_t T1, Triangle_t T2) //TODO: think about receive using const ref in everyone method except manager funtion
    {
        double p2_q2_r2_p1 = det(T2.p(), T2.q(), T2.r(), T1.p());
        double p2_q2_r2_q1 = det(T2.p(), T2.q(), T2.r(), T1.q()); // receive using reference!
        double p2_q2_r2_r1 = det(T2.p(), T2.q(), T2.r(), T1.r());

        if (!std::isnan(p2_q2_r2_p1) && !std::isnan(p2_q2_r2_q1) != NAN && !std::isnan(p2_q2_r2_r1) != NAN)
        {
            if ((cmp::greater(p2_q2_r2_p1, 0) && cmp::greater(p2_q2_r2_q1, 0) && cmp::greater(p2_q2_r2_r1, 0)) ||
                (cmp::less(p2_q2_r2_p1, 0) && cmp::less(p2_q2_r2_q1, 0) && cmp::less(p2_q2_r2_r1, 0)))
            {
                return DOESNT_INTERSECT;
            }
            else if (cmp::is_0(p2_q2_r2_p1) && cmp::is_0(p2_q2_r2_q1) && cmp::is_0(p2_q2_r2_r1))
            {
                return COPLANAR;
            }
            else 
            {
                return INTERSECT;
            }
        }
        else 
        {
            return DOESNT_INTERSECT;
        }
    }

    bool arrange_3D_triangle_points(Triangle_t T1, Triangle_t T2)
    {
        int det_p = det(T2.p(), T2.q(), T2.r(), T1.p()); 
        int det_q = det(T2.p(), T2.q(), T2.r(), T1.q());
        int det_r = det(T2.p(), T2.q(), T2.r(), T1.r());

        if (det_p == 0 && det_q == 0 && det_r == 0)
        {
            return false;
        }
        for (int i = 0; i < 3; ++i)
        {
            if ( (cmp::sign(det_q) == cmp::sign(det_r)) && (cmp::sign(det_p) != cmp::sign(det_q)) ) // by construction, the last check can be removed
            {
                if (cmp::sign(det_p) < 0)
                {
                    T2.swap_q_r();
                    break;
                }
                else if (cmp::sign(det_p) == 0 && cmp::sign(det_q) > 0)
                {
                    T2.swap_q_r();
                }
                break;
            }
            else
            {
                T1.circular_permutation();
            }
            det_p = det(T2.p(), T2.q(), T2.r(), T1.p());
            det_q = det(T2.p(), T2.q(), T2.r(), T1.q());
            det_r = det(T2.p(), T2.q(), T2.r(), T1.r());
        }
        return true;
    }

    bool check_3D_triangles_intersection(Triangle_t T1, Triangle_t T2)
    {
        bool is_arranged = arrange_3D_triangle_points(T1, T2);
        if (!is_arranged)
        {
            return false;
        }

        if (cmp::less_equal(det(T1.p(), T1.q(), T2.p(), T2.q()), 0) && cmp::less_equal(det(T1.p(), T1.r(), T2.r(), T2.p()), 0))
        {
            return true;
        }

        return false; 
    }

    bool p1_belongs_R1(Triangle_t T1, Triangle_t T2)
    {
        if (cmp::greater_equal(det(T2.r(), T2.p(), T1.q()), 0))
        {
            if (cmp::greater_equal(det(T2.r(), T1.p(), T1.q()), 0))
            {
                if (cmp::greater_equal(det(T1.p(), T2.p(), T1.q()), 0))
                    return false;
                else
                {
                    if (cmp::greater_equal(det(T1.p(), T2.p(), T1.r()), 0))
                    {
                        if (cmp::greater_equal(det(T1.q(), T1.r(), T2.p()), 0))
                            return true;
                        else
                            return false;
                    }
                    else
                        return false;
                }
            }
            else
                return false;
        }
        else
        {
            if (cmp::greater_equal(det(T2.r(), T2.p(), T1.r()), 0))
            {
                if (cmp::greater_equal(det(T1.q(), T1.r(), T2.r()), 0))
                {
                    if (cmp::greater_equal(det(T1.p(), T2.p(), T1.r()), 0))
                        return true;
                    else
                        return false;
                }
                else
                    return false;
            }
            else
                return false;
        }
    }

    bool p1_belongs_R2(Triangle_t T1, Triangle_t T2)
    {
        if (cmp::greater_equal(det(T2.r(), T2.p(), T1.q()), 0))
        {
            if (cmp::greater_equal(det(T2.q(), T2.r(), T1.q()), 0))
            {
                if (cmp::greater_equal(det(T1.p(), T2.p(), T1.q()), 0))
                {
                    if (cmp::greater(det(T1.p(), T2.q(), T1.q()), 0))
                        return false;
                    else
                        return true;
                }
                else 
                {
                    if (cmp::greater_equal(det(T1.p(), T2.p(), T1.r()), 0))
                    {
                        if (cmp::greater_equal(det(T2.r(), T2.p(), T1.r()), 0))
                            return true;
                        else
                            return false;
                    }
                    else
                        return false;
                }
            }
            else
            {
                if (cmp::less_equal(det(T1.p(), T2.q(), T1.q()), 0))
                {
                    if (cmp::greater_equal(det(T2.q(), T2.r(), T1.r()), 0))
                    {
                        if (cmp::greater_equal(det(T1.q(), T1.r(), T2.q()), 0))
                            return true;
                        else
                            return false;
                    }
                    else
                        return false;
                }
                else
                    return false;
            }
        }
        else
        {
            if (cmp::greater_equal(det(T2.r(), T2.p(), T1.r()), 0))
            {
                if (cmp::greater_equal(det(T1.q(), T1.r(), T2.r()), 0))
                {
                    if (cmp::greater_equal(det(T1.r(), T1.p(), T2.p()), 0))
                        return true;
                    else
                        return false;
                }
                else
                {
                    if (cmp::greater_equal(det(T1.q(), T1.r(), T2.q()), 0))
                    {
                        if (cmp::greater_equal(det(T2.q(), T2.r(), T1.r()), 0))
                            return true;
                        else
                            return false;
                    }
                    else
                        return false;
                }
            }
            else
                return false;
        }
    }

    bool check_2D_triangles_intersection(Triangle_t T1, Triangle_t T2)
    {
        T1.project_onto_plane();
        T2.project_onto_plane();

        T1.arrange_counterclockwise();
        T2.arrange_counterclockwise();

        double det_p2_q2_p1 = det(T2.p(), T2.q(), T1.p());
        double det_q2_r2_p1 = det(T2.q(), T2.r(), T1.p());
        double det_r2_p2_p1 = det(T2.r(), T2.p(), T1.p());

        if (cmp::is_0(det_q2_r2_p1) && cmp::is_0(det_r2_p2_p1) && cmp::is_0(det_p2_q2_p1))
        {
            return false;
        }
        else if (cmp::greater(det_q2_r2_p1, 0) && cmp::greater(det_r2_p2_p1, 0) && cmp::greater(det_p2_q2_p1, 0))
        {
            return true;
        }
        else if (cmp::is_0(det_q2_r2_p1))
        {
            if (cmp::greater(det_r2_p2_p1, 0) && cmp::greater(det_p2_q2_p1, 0))
                return true;
            else if (cmp::is_0(det_r2_p2_p1))
                return true;
            else if (cmp::is_0(det_p2_q2_p1))
                return true;
            else
                return false;
        }
        else if (cmp::is_0(det_r2_p2_p1))
        {
            if (cmp::greater(det_q2_r2_p1, 0) && cmp::greater(det_p2_q2_p1, 0))
                return true;
            else if (cmp::is_0(det_q2_r2_p1))
                return true;
            else if (cmp::is_0(det_p2_q2_p1))
                return true;
            else
                return false;
        }
        else if (cmp::is_0(det_p2_q2_p1))
        {
            if (cmp::greater(det_q2_r2_p1, 0) && cmp::greater(det_r2_p2_p1, 0))
                return true;
            else if (cmp::is_0(det_q2_r2_p1))
                return true;
            else if (cmp::is_0(det_r2_p2_p1))
                return true;
            else 
                return false;
        }

        
        for (int i = 0; i < 3; ++i)
        {
            if (cmp::greater(det_p2_q2_p1, 0) && cmp::less(det_q2_r2_p1, 0) && cmp::less(det_r2_p2_p1, 0))
            {
                return p1_belongs_R2(T1, T2);
            }
            if (cmp::greater(det_p2_q2_p1, 0) && cmp::greater(det_q2_r2_p1, 0) && cmp::less(det_r2_p2_p1, 0))
            {
                return p1_belongs_R1(T1, T2);
            }
            T2.circular_permutation();

            det_p2_q2_p1 = det(T2.p(), T2.q(), T1.p());
            det_q2_r2_p1 = det(T2.q(), T2.r(), T1.p());
            det_r2_p2_p1 = det(T2.r(), T2.p(), T1.p());
        }

        return false;
    }


    bool intersection_3D_triangles(Triangle_t T1, Triangle_t T2)
    {
        Positions result1 = intersection_of_triangle_and_plane(T1, T2);
        Positions result2 = intersection_of_triangle_and_plane(T2, T1);

        if (result1 == INTERSECT && result2 == INTERSECT)
        {
            return check_3D_triangles_intersection(T1, T2);
        }
        else if (result1 == COPLANAR && result2 == COPLANAR)
        {
            return check_2D_triangles_intersection(T1, T2);
        }
        else
        {
            return false;
        }
    }



}

#endif