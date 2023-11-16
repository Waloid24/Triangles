#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

class Point_t final {

        double x_= NAN, y_ = NAN, z_ = NAN;
        using coord_it = typename std::vector<double>::iterator;

        public:

            Point_t(double x, double y, double z) : x_{x}, y_{y}, z_{z} {}

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

    typedef enum Axes {
        X,
        Y,
        Z
    } Axes;

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

#endif