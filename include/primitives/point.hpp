#ifndef POINT_HPP
#define POINT_HPP

class Point_t {

        double x_= NAN, y_ = NAN, z_ = NAN;

        public:

            Point_t(double x, double y, double z) : x_{x}, y_{y}, z_{z} {};
            
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

            void print() const { std::cout << "(" << x_ << " ; " << y_ << " ; " << z_ << ")" << std::endl; }
    };


#endif 