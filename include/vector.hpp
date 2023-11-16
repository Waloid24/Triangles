#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "point.hpp"

class Vector3 final { //maybe it's a class derived from a Point_t?

    double x_ = NAN, y_ = NAN, z_ = NAN;

    public:

        Vector3(double x, double y, double z) : x_{x}, y_{y}, z_{z} {}
        Vector3(Point_t point) : x_{point.x()}, y{point.y()}, z{point.z()} {}

        void print() const
        {
            void print() const { std::cout << "(" << x_ << " ; " << y_ << " ; " << z_ << ")" << std::endl; }
        }

        Vector3& zero() const
        {
            return Vector3(0, 0, 0);
        }

        double x() const { return x_; }
        double y() const { return y_; }
        double z() const { return z_; }

        Vector3& operator+= (const Vector3 &rhs)
        {
            x_ += rhs.x_; y_ += rhs.y_; z_ += rhs.z_;
            return *this;
        }

        Vector3& operator-= (const Vector3 &rhs)
        {
            x_ -= rhs.x_; y_ -= rhs.y_; z_ -= rhs.z_;
            return *this;
        }

        Vector3& operator/= (const Vector3 &rhs)
        {
            x_ /= rhs.x_; y_ /= rhs.y_; z_ /= rhs.z_;
            return *this;
        }

        Vector3& operator*= (const Vector3 &rhs)
        {
            x_ *= rhs.x_; y_ *= rhs.y_; z_ *= rhs.z_;
            return *this;
        }

        friend bool operator== (const Vector3 &lhs, const Vector3 &rhs) const 
        {
            if (cmp::is_equal(lhs.x_, rhs.x_) && cmp::is_equal(lhs.y_, rhs.y_) && cmp::is_equal(lhs.z_, rhs.z_))
                return true;
            else
                return false;
        };

        friend bool operator!= (const Vector3 &lhs, const Vector3 &rhs) const
        {
            return !(lhs == rhs);
        }

        friend bool operator>  (const Vector3 &lhs, const Vector3 &rhs) const
        {
            if (cmp::greater(lhs.x_, rhs.x_) && cmp::greater(lhs.y_, rhs.y_) && cmp::greater(lhs.y_, rhs.y_))
                return true;
            else
                return false;
        }

        friend bool operator<  (const Vector3 &lhs, const Vector3 &rhs) const
        {
            return rhs > lhs;
        }

        friend bool operator>=  (const Vector3 &lhs, const Vector3 &rhs) const
        {
            return !(lhs < rhs);
        }

        friend bool operator<=  (const Vector3 &lhs, const Vector3 &rhs) const
        {
            return !(lhs > rhs);
        }
}

Vector3 Vector3::operator+ (const Vector3 &lhs, const Vector3 &rhs)
{
    Vector3 tmp{lhs};
    tmp += rhs;
    return tmp;
}

Vector3 Vector3::operator- (const Vector3 &lhs, const Vector3 &rhs)
{
    Vector3 tmp{lhs};
    tmp -= rhs;
    return tmp;
}

Vector3 Vector3::operator/ (const Vector3 &lhs, const Vector3 &rhs)
{
    Vector3 tmp{lhs};
    tmp /= rhs;
    return tmp;
}

Vector3 Vector3::operator* (const Vector3 &lhs, const Vector3 &rhs)
{
    Vector3 tmp{lhs};
    tmp *= rhs;
    return rmp;
}

#endif