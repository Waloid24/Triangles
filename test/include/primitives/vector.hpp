#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <utility>
#include <cmath>
#include <vector>
#include <algorithm>

#include "../maths/maths.hpp"

namespace lingeo {

class Vector final {

    double coords_[3];

    public:

        Vector(double x, double y, double z) : coords_{x, y, z} {}
        Vector(const Vector &vec) : coords_{vec.x(), vec.y(), vec.z()} {}
        Vector(const double num) : coords_{num, num, num} {}

        void change_values(double x, double y, double z) //TODO: delete this shit
        {
            coords_[0] = x; coords_[1] = y; coords_[2] = z;
        }

        bool is_null() const {
            return (maths::is_0(coords_[0]) && maths::is_0(coords_[1]) && maths::is_0(coords_[2]));
        }

        void print() const { std::cout << "(" << coords_[0] << " ; " << coords_[1] << " ; " << coords_[2] << ")" << std::endl; }

        double x() const { return coords_[0]; }
        double y() const { return coords_[1]; }
        double z() const { return coords_[2]; }

        Vector& operator+= (const Vector &rhs)
        {
            coords_[0] += rhs.x(); coords_[1] += rhs.y(); coords_[2] += rhs.z();
            return *this;
        }

        Vector& operator-= (const Vector &rhs)
        {
            coords_[0] -= rhs.x(); coords_[1] -= rhs.y(); coords_[2] -= rhs.z();
            return *this;
        }

        Vector& operator/= (const Vector &rhs)
        {
            if (!maths::is_0(rhs.x()) && !maths::is_0(rhs.y()) && !maths::is_0(rhs.z()))
                coords_[0] /= rhs.x(); coords_[1] /= rhs.y(); coords_[2] /= rhs.z();
            return *this;
        }

        Vector& operator*= (const Vector &rhs)
        {
            coords_[0] *= rhs.x(); coords_[1] *= rhs.y(); coords_[2] *= rhs.z();
            return *this;
        }
};

bool operator== (const Vector &lhs, const Vector &rhs)
{
    if (maths::is_equal(lhs.x(), rhs.x()) && maths::is_equal(lhs.y(), rhs.y()) && maths::is_equal(lhs.z(), rhs.z()))
        return true;
    else
        return false;
};

bool operator!= (const Vector &lhs, const Vector &rhs)
{
    return !(lhs == rhs);
}

bool operator>  (const Vector &lhs, const Vector &rhs)
{
    if (maths::greater(lhs.x(), rhs.x()) && maths::greater(lhs.y(), rhs.y()) && maths::greater(lhs.z(), rhs.z()))
        return true;
    else
        return false;
}

bool operator<  (const Vector &lhs, const Vector &rhs)
{
    return rhs > lhs;
}

bool operator>=  (const Vector &lhs, const Vector &rhs)
{
    return !(lhs < rhs);
}

bool operator<=  (const Vector &lhs, const Vector &rhs)
{
    return !(lhs > rhs);
}

Vector operator+ (const Vector &lhs, const Vector &rhs)
{
    Vector tmp{lhs};
    tmp += rhs;
    return tmp;
}

Vector operator- (const Vector &lhs, const Vector &rhs)
{
    Vector tmp{lhs};
    tmp -= rhs;
    return tmp;
}

Vector operator/ (const Vector &lhs, const Vector &rhs)
{
    Vector tmp{lhs};
    tmp /= rhs;
    return tmp;
}

Vector operator/ (const Vector &lhs, const double &num)
{
    Vector tmp{num};
    return lhs / tmp;
}

Vector operator* (const Vector &lhs, const Vector &rhs)
{
    Vector tmp{lhs};
    tmp *= rhs;
    return tmp;
}

std::ostream &operator<< (std::ostream &os, const Vector& vec)
{
    os << "(" << vec.x() << " ; " << vec.y() << " ; " << vec.z() << ")" << std::endl;
    return os;
}

enum class Location_3D {
        
    BELOW = -1,
    ON    = 0,
    ABOVE = 1

};

inline Location_3D position_3D(const Vector &a, const Vector &b, const Vector &c, const Vector &d)
{
    double det =    (a.x()-d.x())*( (b.y()-d.y())*(c.z()-d.z()) - (c.y()-d.y())*(b.z()-d.z()) ) -
                    (a.y()-d.y())*( (b.x()-d.x())*(c.z()-d.z()) - (c.x()-d.x())*(b.z()-d.z()) ) +
                    (a.z()-d.z())*( (b.x()-d.x())*(c.y()-d.y()) - (b.y()-d.y())*(c.x()-d.x()) );
    
    if (maths::is_0(det))
        return Location_3D::ON;
    else if (maths::greater(det, 0))
        return Location_3D::ABOVE;
    else
        return Location_3D::BELOW;
}

enum Axes {
    X,
    Y,
    Z
};

enum class Location_2D {
        
    LEFT  = 0,
    ON    = 1,
    RIGHT = 2

};

inline Location_2D position_2D(const Vector &a, const Vector &b, const Vector &c, Axes axis = Z)
{
    double det;

    if (axis == Z)
        det = a.x()*(b.y() - c.y()) - a.y()*(b.x() - c.x()) + b.x()*c.y() - c.x()*b.y();
    else if (axis == Y)
        det = a.x()*(c.z() - b.z()) - (b.x()*c.z() - c.x()*b.z()) + a.z()*(b.x() - c.x());
    else 
        det = b.y()*c.z() - c.y()*b.z() - a.y()*(c.z() - b.z()) + a.z()*(c.y() - b.y());

    if (maths::is_0(det))
        return Location_2D::ON;
    else if (maths::greater(det, 0))
        return Location_2D::RIGHT;
    else
        return Location_2D::LEFT;
}

} /* namespace lingeo */

#endif