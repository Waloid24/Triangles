#ifdef LINGEO_HPP
#define LINGEO_HPP

#include <iostream>
#include <cmath>

namespace lingeo {

    class Point_t {

        double x_= NaN, y_ = NaN, z_ = NaN;

        public:

            Point_t(double x, double y, double z) : x_{x}, y_{y}, z_{z} {};

            void print() const { std::cout << "(" << x_ << " ; " << y_ << " ; " << z_ << ")" << std::endl; }
            
            int valid() const { 
                if (isnan(x_) || isnan(y_) || isnan(z_)) 
                    return 1;
                else
                    return 0;
            }

            double x() { return x_; }
            double y() { return y_; }
            double z() { return z_; }
    };

    class Triangle_t {

        Point_t p_, q_, r_;

        public:

            Triangle_t( double p_x, double p_y, double p_z, 
                        double q_x, double q_y, double q_z,
                        double r_x, double r_y, double r_z ) : p_{p_x, p_y, p_z}, q_{q_x, q_y, q_z}, r_{r_x, r_y, r_z} {};
        
            Point_t get_p() { return p_; }
            Point_t get_q() { return q_; }
            Point_t get_r() { return r_; }

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
            return NaN;
        }
    }

    double det_abc(Point_t a, Point_t b, Point_t c)
    {
        if (a.valid() && b.valid() && c.valid())
        {
            return a.x()*(b.y() - c.y()) - a.y()*(b.x() - c.x()) + b.x()*c.y() - c.x()*b.y();
        }
        else
        {
            return NaN;
        }
    }

    enum Positions {
        DOESNT_INTERSECT = 0,
        INTERSECT = 1,
        COMPLANAR = 2
    };

    enum Positions position_of_trinagle_and_plane(Triangle_t T1, Triangle_t T2) 
    {
        double p2_q2_r2_p1 = det_abcd(T2.get_p(), T2.get_q(), T2.get_r(), T1.get_p());
        double p2_q2_r2_q1 = det_abcd(T2.get_p(), T2.get_q(), T2.get_r(), T1.get_q());
        double p2_q2_r2_r1 = det_abcd(T2.get_p(), T2.get_q(), T2.get_r(), T1.get_r());

        if (!isnan(p2_q2_r2_p1) && !isnan(p2_q2_r2_q1) != NaN && !isnan(p2_q2_r2_r1) != NaN)
        {
            if ((p2_q2_r2_p1 > 0 && p2_q2_r2_q1 > 0 && p2_q2_r2_r1 > 0) ||
                (p2_q2_r2_p1 < 0 && p2_q2_r2_q1 < 0 && p2_q2_r2_r1 < 0))
            {
                return DOESNT_INTERSECT;
            }
            else if (p2_q2_r2_p1 == 0 && p2_q2_r2_q1 == 0 && p2_q2_r2_r1 == 0)
            {
                return COMPLANAR;
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


    bool intersection_3D_triangles()
    {
        
    }


}

#endif