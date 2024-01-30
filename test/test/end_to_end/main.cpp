#include <iostream>
#include <vector>
#include <cmath>

#include "../../include/primitives/triangle.hpp"
#include "../../include/dividing_space/octree.hpp"
#include "../../include/maths/maths.hpp"

#define NO_DEBUG

const int NUMBER_OF_COORDINATES = 3;
const int NUMBER_OF_DOTS = 3;

int main ()
{
    // size_t n_triangles = 2;
    size_t n_triangles;
    std::cin >> n_triangles;

    // std::vector<double> coordinates{0, 0, 0, 2, -2, 0, 2, 1, 0, 2.75, 3.00, 0, 1.94, -2.42, 0, 2.1, -2.67, 0};
    std::vector<double> coordinates;
    std::vector<lingeo::Vector> points;
    std::vector<lingeo::Triangle> triangles;

    using coord_it  = typename std::vector<double>::iterator;
    using points_it = typename std::vector<lingeo::Vector>::iterator;

    coord_it begin = coordinates.begin();
    coord_it end   = coordinates.end();
    size_t n_coordinates = n_triangles*9;

    double largest_number = 0;

    for (size_t i = 1; i <= n_coordinates; ++i, ++end)
    {
        double coordinate;
        std::cin >> coordinate;

        coordinates.push_back(coordinate);

        if (maths::greater(coordinate, largest_number))
            largest_number = coordinate;

        if (i % 3 == 0)
        {
            points.emplace_back(coordinates[i-3], coordinates[i-2], coordinates[i-1]);
            begin = end;
        }
    }

    for (size_t i = 0, j = 0; i < n_triangles*3; i=i+3, ++j)
    {
        triangles.emplace_back(points[i], points[i+1], points[i+2]);
        std::prev(triangles.end())->add_number(j);
    }

    long long largest_power_of_two = maths::find_largest_pow_of_two(maths::round(std::abs(largest_number)));

    lingeo::Vector vec1{largest_power_of_two};
    lingeo::Vector vec2{-largest_power_of_two};
    // lingeo::Vector vec1{4};
    // lingeo::Vector vec2{-4};

    lingeo::Bounding_box region{vec1, vec2};

    octree::OctTree_t octree{region, triangles.begin(), triangles.end()};
    
    octree.count_intersection_in_octree();

    lingeo::Triangle::show_intersect_triangles();    
}