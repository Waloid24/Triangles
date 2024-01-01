#ifndef LINGEO_HPP
#define LINGEO_HPP

#include <iostream>
#include <tuple>
#include "double_comparison.hpp"
#include "vector.hpp"
#include "bounding_objs.hpp"

namespace lingeo {

    enum Triangle_Position {
        
        DOESNT_INTERSECT,
        INTERSECT,
        COPLANAR

    };
    
    class Triangle final {

        Vector_3D p_, q_, r_;
        Bounding_box box_;
        size_t number;
        static std::vector<size_t> intersecting_triangles;

        bool check_entry_into_set(size_t num_tr)
        {
            for (auto it = intersecting_triangles.begin(), ite = intersecting_triangles.end();
                it != ite; ++it)
            {
                if (*it == num_tr)
                    return true;
            }
            return false;
        }

        public:

            Triangle(const Vector_3D &p, const Vector_3D &q, const Vector_3D &r) : p_{p}, q_{q}, r_{r} {

                double loc_min_x;
                double loc_max_x;

                double loc_min_y;
                double loc_max_y;

                double loc_min_z;
                double loc_max_z;

                loc_max_x = cmp::greater(p.x(), q.x()) ? (cmp::greater(p.x(),r.x()) ? p.x() : r.x()) :
                                                         (cmp::greater(q.x(),r.x()) ? q.x() : r.x());

                loc_max_y = cmp::greater(p.y(), q.y()) ? (cmp::greater(p.y(),r.y()) ? p.y() : r.y()) :
                                                         (cmp::greater(q.y(),r.y()) ? q.y() : r.y());
                
                loc_max_z = cmp::greater(p.z(), q.z()) ? (cmp::greater(p.z(),r.z()) ? p.z() : r.z()) :
                                                         (cmp::greater(q.z(),r.z()) ? q.z() : r.z());

                loc_min_x = cmp::less(p.x(), q.x()) ?    (cmp::less(p.x(),r.x()) ? p.x() : r.x()) :
                                                         (cmp::less(q.x(),r.x()) ? q.x() : r.x());

                loc_min_y = cmp::less(p.y(), q.y()) ?    (cmp::less(p.y(),r.y()) ? p.y() : r.y()) :
                                                         (cmp::less(q.y(),r.y()) ? q.y() : r.y());
                
                loc_min_z = cmp::less(p.z(), q.z()) ?    (cmp::less(p.z(),r.z()) ? p.z() : r.z()) :
                                                         (cmp::less(q.z(),r.x()) ? q.z() : r.z());

                Vector_3D loc_max{loc_max_x, loc_max_y, loc_max_z};
                Vector_3D loc_min{loc_min_x, loc_min_y, loc_min_z};

                Bounding_box tmp{loc_min, loc_max, true};
                box_ = tmp;

            }

            static void show_intersect_triangles()
            {
                std::sort(intersecting_triangles.begin(),intersecting_triangles.end());

                for (auto it = intersecting_triangles.begin(), ite = intersecting_triangles.end();
                        it != ite; ++it)
                {
                    std::cout << *it << " ";
                }
            }

            void add_number(size_t num)
            {
                number = num;
            }

            void add_to_intersect_triangles()
            {
                if (!check_entry_into_set(number))
                {
                    intersecting_triangles.push_back(number);
                }
            }

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
                    swap_q_r();
            }

            void swap_clockwise()
            {
                std::swap (p_, r_);
                std::swap (q_, r_);
            }

            void swap_counterclockwise()
            {
                std::swap (p_, q_);
                std::swap (r_, q_);
            }
            
            void circular_permutation()
            {
                Vector_3D temp_r = r_;
                Vector_3D temp_q = q_;
                q_ = p_;
                r_ = temp_q;
                p_ = temp_r;
            }

            Vector_3D get_min_vec() const
            {
                return box_.min();
            }

            Vector_3D get_max_vec() const
            {
                return box_.max();
            }

            Bounding_box get_bounding_box() const 
            {
                return box_;
            }


            Vector_3D p() const { return p_; }
            Vector_3D q() const { return q_; } 
            Vector_3D r() const { return r_; }
    };
    std::vector<size_t> Triangle::intersecting_triangles;

    enum Triangle_Location_3D {
        
        BELOW = -1,
        ON    = 0,
        ABOVE = 1

    };

    Triangle_Location_3D get_point_location(const lingeo::Vector_3D &a, const lingeo::Vector_3D &b, 
                                const lingeo::Vector_3D &c, const lingeo::Vector_3D &d)
    {
        double loc = determ(a, b, c, d);

        if (cmp::is_0(loc))
            return Triangle_Location_3D::ON;
        else if (cmp::greater(loc, 0))
            return Triangle_Location_3D::ABOVE;
        else
            return Triangle_Location_3D::BELOW;
    }

    std::tuple<Triangle_Location_3D, Triangle_Location_3D, Triangle_Location_3D> get_rel_location(const Triangle &T1, const Triangle &T2)
    {
        Triangle_Location_3D pos_P = get_point_location(T2.p(), T2.q(), T2.r(), T1.p());
        Triangle_Location_3D pos_Q = get_point_location(T2.p(), T2.q(), T2.r(), T1.q());
        Triangle_Location_3D pos_R = get_point_location(T2.p(), T2.q(), T2.r(), T1.r());

        return std::tuple{pos_P, pos_Q, pos_R};
    }

    Triangle_Position triangle_and_plane_intersection(const Triangle &T1, const Triangle &T2) 
    {
        auto [P1_loc, Q1_loc, R1_loc] = get_rel_location(T1, T2);

        if ((P1_loc == Triangle_Location_3D::ABOVE && Q1_loc == Triangle_Location_3D::ABOVE && R1_loc == Triangle_Location_3D::ABOVE) ||
            (P1_loc == Triangle_Location_3D::BELOW && Q1_loc == Triangle_Location_3D::BELOW && R1_loc == Triangle_Location_3D::BELOW))
        {
            return Triangle_Position::DOESNT_INTERSECT;
        }
        else if (P1_loc == Triangle_Location_3D::ON && Q1_loc == Triangle_Location_3D::ON && R1_loc == Triangle_Location_3D::ON)
        {
            return Triangle_Position::COPLANAR;
        }
        else 
        {
            return Triangle_Position::INTERSECT;
        }
    }

    inline void arrange_triangles_3D(Triangle &T1, Triangle_Location_3D P1_loc, Triangle_Location_3D Q1_loc, Triangle_Location_3D R1_loc,
                                     Triangle &T2)
    {
        switch (P1_loc)
        {
            case Triangle_Location_3D::ABOVE:
            
                if (Q1_loc == Triangle_Location_3D::ABOVE && R1_loc != Triangle_Location_3D::ABOVE)
                {
                    T1.swap_clockwise();
                    T2.swap_q_r();
                }
                else if (Q1_loc != Triangle_Location_3D::ABOVE && R1_loc == Triangle_Location_3D::ABOVE)
                {
                    T1.swap_counterclockwise();
                    T2.swap_q_r();
                }
                break;

            case Triangle_Location_3D::ON:

                if (Q1_loc == Triangle_Location_3D::ABOVE)
                {
                    if (R1_loc == Triangle_Location_3D::ABOVE)
                        T2.swap_q_r();
                    else
                        T1.swap_counterclockwise();
                }
                else if (R1_loc == Triangle_Location_3D::ABOVE)
                    T1.swap_clockwise();
                else if (Q1_loc == Triangle_Location_3D::ON && R1_loc == Triangle_Location_3D::BELOW)
                {
                    T1.swap_clockwise();
                    T2.swap_q_r();
                }
                else if (Q1_loc == Triangle_Location_3D::BELOW && R1_loc == Triangle_Location_3D::ON)
                {
                    T1.swap_counterclockwise();
                    T2.swap_q_r();
                }
                break;

            case Triangle_Location_3D::BELOW:

                if (Q1_loc == R1_loc)
                    T2.swap_q_r();
                else if (Q1_loc == Triangle_Location_3D::BELOW)
                    T1.swap_clockwise();
                else if (R1_loc == Triangle_Location_3D::BELOW)
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

        P1_loc = get_point_location(T2.p(), T2.q(), T2.r(), T1.p());
        Q2_loc = get_point_location(T1.p(), T1.q(), T1.r(), T2.q());
        R2_loc = get_point_location(T1.p(), T1.q(), T1.r(), T2.r());

        arrange_triangles_3D(T2, P2_loc, Q2_loc, R2_loc, T1);

        P2_loc = get_point_location(T1.p(), T1.q(), T1.r(), T2.p());

        if (P1_loc == Triangle_Location_3D::ON && P2_loc == Triangle_Location_3D::ON)
            return (T1.p() == T2.p());
        else
        {
            auto KJ_mut_pos = get_point_location(T1.p(), T1.q(), T2.p(), T2.q());
            auto LI_mut_pos = get_point_location(T1.p(), T1.r(), T2.p(), T2.r());
            return (KJ_mut_pos != Triangle_Location_3D::ABOVE && LI_mut_pos != Triangle_Location_3D::BELOW);
        }
    }

    inline bool p1_belongs_R1(const Triangle &T1, const Triangle &T2)
    {
        if (cmp::greater_equal(det(T2.r(), T2.p(), T1.q()), 0))
        {
            if (cmp::greater_equal(det(T2.r(), T1.p(), T1.q()), 0))
            {
                if (cmp::greater_equal(det(T1.p(), T2.p(), T1.q()), 0))
                    return true;
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

    inline bool p1_belongs_R2(const Triangle &T1, const Triangle &T2)
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

    inline bool triangles_intersection_2D(Triangle &T1, Triangle &T2)
    {
        T1.project_onto_plane();
        T2.project_onto_plane();

        T1.arrange_counterclockwise();
        T2.arrange_counterclockwise();

        double det_p2_q2_p1 = det(T2.p(), T2.q(), T1.p());
        double det_q2_r2_p1 = det(T2.q(), T2.r(), T1.p());
        double det_r2_p2_p1 = det(T2.r(), T2.p(), T1.p());

        if (cmp::is_0(det_q2_r2_p1) && cmp::is_0(det_r2_p2_p1) && cmp::is_0(det_p2_q2_p1))
            return false;
        else if (cmp::greater(det_q2_r2_p1, 0) && cmp::greater(det_r2_p2_p1, 0) 
                                               && cmp::greater(det_p2_q2_p1, 0))
            return true;
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
            if (cmp::greater_equal(det_p2_q2_p1, 0) && cmp::less_equal(det_q2_r2_p1, 0) && cmp::less_equal(det_r2_p2_p1, 0))
                return p1_belongs_R2(T1, T2);
            if (cmp::greater(det_p2_q2_p1, 0) && cmp::greater(det_q2_r2_p1, 0) && cmp::less(det_r2_p2_p1, 0))
                return p1_belongs_R1(T1, T2);

            T2.circular_permutation();

            det_p2_q2_p1 = det(T2.p(), T2.q(), T1.p());
            det_q2_r2_p1 = det(T2.q(), T2.r(), T1.p());
            det_r2_p2_p1 = det(T2.r(), T2.p(), T1.p());
        }

        return false;
    }


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