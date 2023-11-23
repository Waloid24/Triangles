#include <iostream>
#include <vector>
#include "../../include/triangle.hpp"
#include "../../include/octree.hpp"

const int NUMBER_OF_COORDINATES = 3;
const int NUMBER_OF_DOTS = 3;

int main ()
{
    int n_triangles = 2;

    #if 0
    std::cin >> n_triangles;
    #endif

    std::vector<double> coordinates = {2.416645, 6.647085, -10.662809, 14.70899, 15.388164, -1.960863, 8.723917, 0.007999, 4.339338, 10.273492, 12.808005, 3.161949, 13.316385, -3.713318, 10.829694, 13.68163, 0.664623, 3.303696};
    std::vector<lingeo::Point_t> points;
    std::vector<lingeo::Triangle_t> triangles;

    using coord_it  = typename std::vector<double>::iterator;
    using points_it = typename std::vector<lingeo::Point_t>::iterator;

    coord_it begin = coordinates.begin();
    coord_it end   = coordinates.end();
    int n_coordinates = n_triangles*9;

    for (int i = 1; i <= n_coordinates; ++i, ++end)
    {

        #if 0
        double coordinate;
        std::cin >> coordinate;
        coordinates.push_back(coordinate);
        #endif


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

    bool result = intersection_3D_triangles(triangles[0], triangles[1]);

    #if 0
    if (result)
    {
        std::cout << "\033[32;1m INTERSECT \033[0m" << std::endl;
    }
    else
    {
        std::cout << "\033[31;1m DOESN'T INTERSECT \033[0m" << std::endl;
    }
    #endif

    lingeo::Vector3 vec1{16, 16, 16};
    lingeo::Vector3 vec2{-16, -16, -16};

    lingeo::Bounding_box region{vec1, vec2};

    octree::OctTree_t octree{region, triangles.begin(), triangles.end()};
    
    std::cout << octree.count_intersection_in_octree() << std::endl;
    
}