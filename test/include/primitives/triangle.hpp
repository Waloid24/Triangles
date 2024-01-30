#ifndef LINGEO_HPP
#define LINGEO_HPP

#include <algorithm>
#include <iostream>
#include <iterator>
#include <initializer_list>

#include "vector.hpp"

namespace lingeo {

    class Triangle final {

        Vector points_[3];
        size_t number_;

        static std::vector<size_t> intersecting_triangles;
        bool check_entry_into_set(size_t num_tr)
        {
            for (auto elem : intersecting_triangles)
            {
                if (elem == num_tr)
                    return true;
            }
            return false;
        }

        public:

            Triangle(const Vector &p, const Vector &q, const Vector &r) : points_{p, q, r} {}

            void print() const {
                std::cout << "p" << points_[0] << std::endl;

                std::cout << "q" << points_[1] << std::endl;

                std::cout << "r" << points_[2] << std::endl;
            }

            void swap_q_r()
            {
                std::swap(points_[1], points_[2]);
            }

            void arrange_counterclockwise()
            {
                if (position_2D(points_[0], points_[1], points_[2]) == Location_2D::LEFT)
                    swap_q_r();
            }

            void swap_clockwise()
            {
                std::swap(points_[0], points_[2]);
                std::swap(points_[1], points_[2]);
            }

            void swap_counterclockwise()
            {
                std::swap(points_[0], points_[1]);
                std::swap(points_[2], points_[1]);
            }

            void circular_permutation()
            {
                Vector temp_r = points_[2];
                Vector temp_q = points_[1];
                points_[1] = points_[0];
                points_[2] = temp_q;
                points_[0] = temp_r;
            }

            Vector p() const { return points_[0]; }
            Vector q() const { return points_[1]; } 
            Vector r() const { return points_[2]; }

            const Vector* begin() { return std::begin(points_); }
            const Vector* end()   { return std::end(points_);   }

            static void show_intersect_triangles()
            {
                std::sort(intersecting_triangles.begin(),intersecting_triangles.end());

                for (auto triangle : intersecting_triangles)
                {
                    std::cout << triangle << '\n';
                }
            }

            void add_number(size_t num)
            {
                number_ = num;
            }

            void add_to_intersect_triangles()
            {
                if (!check_entry_into_set(number_))
                {
                    intersecting_triangles.push_back(number_);
                }
            }
    };
    std::vector<size_t> Triangle::intersecting_triangles;

}

#endif