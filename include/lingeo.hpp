#ifdef LINGEO_HPP
#define LINGEO_HPP

#include <iostream>
#include <math>

namespace lingeo {

    class point_t final {

        double x_= NaN, y_ = NaN, z_ = NaN;

        public:

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

    double det_abcd(point_t a, point_t b, point_t c, point_t d)
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


}

#endif