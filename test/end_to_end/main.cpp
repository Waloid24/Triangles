#include <iostream>
#include <vector>
#include <cmath>

#include "../../include/triangle.hpp"
#include "../../include/octree.hpp"
#include "../../include/maths.hpp"

#define NO_DEBUG

const int NUMBER_OF_COORDINATES = 3;
const int NUMBER_OF_DOTS = 3;

int main ()
{
    int n_triangles;
    std::cin >> n_triangles;

    std::vector<double> coordinates;
    std::vector<lingeo::Vector_3D> points;
    std::vector<lingeo::Triangle> triangles;

    using coord_it  = typename std::vector<double>::iterator;
    using points_it = typename std::vector<lingeo::Vector_3D>::iterator;

    coord_it begin = coordinates.begin();
    coord_it end   = coordinates.end();
    int n_coordinates = n_triangles*9;

    double largest_number = 0;

    for (int i = 1; i <= n_coordinates; ++i, ++end)
    {
        double coordinate;
        std::cin >> coordinate;

        coordinates.push_back(coordinate);

        if (cmp::greater(coordinate, largest_number))
            largest_number = coordinate;

        if (i % 3 == 0)
        {
            points.emplace_back(coordinates[i-3], coordinates[i-2], coordinates[i-1]);
            begin = end;
        }
    }

    for (int i = 0; i < n_triangles*3; i=i+3)
    {
        triangles.emplace_back(points[i], points[i+1], points[i+2]);
    }

    long long largest_power_of_two = maths::find_largest_pow_of_two(cmp::round(std::abs(largest_number)));

    lingeo::Vector_3D vec1{largest_power_of_two};
    lingeo::Vector_3D vec2{-largest_power_of_two};

    lingeo::Bounding_box region{vec1, vec2};

    octree::OctTree_t octree{region, triangles.begin(), triangles.end()};
    
    std::cout << octree.count_intersection_in_octree() << std::endl;
    
}