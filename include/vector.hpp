#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <utility>
#include <cmath>

#include "double_comparison.hpp"

namespace lingeo
{

class Vector_3D final {

    double x_ = NAN, y_ = NAN, z_ = NAN;

    public:

        Vector_3D(){}
        Vector_3D(double x, double y, double z) : x_{x}, y_{y}, z_{z} {}
        Vector_3D(double num) : x_{num}, y_{num}, z_{num} {}

        void change_values(double x, double y, double z)
        {
            x_ = x;
            y_ = y;
            z_ = z;
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

        bool is_null() const {
            return (cmp::is_0(x_) && cmp::is_0(y_) && cmp::is_0(z_));
        }

        int valid() const { 
            return !(std::isnan(x_) || std::isnan(y_) || std::isnan(z_));
        }

        void print() const { std::cout << "(" << x_ << " ; " << y_ << " ; " << z_ << ")" << std::endl; }

        double x() const { return x_; }
        double y() const { return y_; }
        double z() const { return z_; }

        Vector_3D& operator+= (const Vector_3D &rhs)
        {
            x_ += rhs.x_; y_ += rhs.y_; z_ += rhs.z_;
            return *this;
        }

        Vector_3D& operator-= (const Vector_3D &rhs)
        {
            x_ -= rhs.x_; y_ -= rhs.y_; z_ -= rhs.z_;
            return *this;
        }

        Vector_3D& operator/= (const Vector_3D &rhs)
        {
            if (!cmp::is_0(rhs.x_) && !cmp::is_0(rhs.y_) && !cmp::is_0(rhs.z_))
                x_ /= rhs.x_; y_ /= rhs.y_; z_ /= rhs.z_;
            return *this;
        }

        Vector_3D& operator*= (const Vector_3D &rhs)
        {
            x_ *= rhs.x_; y_ *= rhs.y_; z_ *= rhs.z_;
            return *this;
        }
};

bool operator== (const Vector_3D &lhs, const Vector_3D &rhs)
{
    if (cmp::is_equal(lhs.x(), rhs.x()) && cmp::is_equal(lhs.y(), rhs.y()) && cmp::is_equal(lhs.z(), rhs.z()))
        return true;
    else
        return false;
};

bool operator!= (const Vector_3D &lhs, const Vector_3D &rhs)
{
    return !(lhs == rhs);
}

bool operator>  (const Vector_3D &lhs, const Vector_3D &rhs)
{
    if (cmp::greater(lhs.x(), rhs.x()) && cmp::greater(lhs.y(), rhs.y()) && cmp::greater(lhs.z(), rhs.z()))
        return true;
    else
        return false;
}

bool operator<  (const Vector_3D &lhs, const Vector_3D &rhs)
{
    return rhs > lhs;
}

bool operator>=  (const Vector_3D &lhs, const Vector_3D &rhs)
{
    return !(lhs < rhs);
}

bool operator<=  (const Vector_3D &lhs, const Vector_3D &rhs)
{
    return !(lhs > rhs);
}

Vector_3D operator+ (const Vector_3D &lhs, const Vector_3D &rhs)
{
    Vector_3D tmp{lhs};
    tmp += rhs;
    return tmp;
}

Vector_3D operator- (const Vector_3D &lhs, const Vector_3D &rhs)
{
    Vector_3D tmp{lhs};
    tmp -= rhs;
    return tmp;
}

Vector_3D operator/ (const Vector_3D &lhs, const Vector_3D &rhs)
{
    Vector_3D tmp{lhs};
    tmp /= rhs;
    return tmp;
}

Vector_3D operator/ (const Vector_3D &lhs, const double &num)
{
    Vector_3D tmp{num};
    return lhs / tmp;
}

Vector_3D operator* (const Vector_3D &lhs, const Vector_3D &rhs)
{
    Vector_3D tmp{lhs};
    tmp *= rhs;
    return tmp;
}

inline double determ(const Vector_3D &a, const Vector_3D &b, const Vector_3D &c, const Vector_3D &d)
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

enum Axes {
    X,
    Y,
    Z
};

inline double det(const Vector_3D &a, const Vector_3D &b, const Vector_3D &c, Axes axis = Z)
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

} /* namespace lingeo */

#endif