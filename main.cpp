#include <iostream>
#include <vector>
#include "include/lingeo.hpp"


const int NUMBER_OF_COORDINATES = 3;
const int NUMBER_OF_DOTS = 3;

/*

окто-дерево для пространства, сделать это перед end-to-end

*/

int main (int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "You should enter one arguments: the number of triangles" << std::endl;
        return 1;
    }


    int triangles_num = std::atoi(argv[1]);

    std::cout << "Please enter " << triangles_num << " sets of dots of five dots each to create triangles: " << std::endl;

    std::vector<double> dots_array_1;
    for (int i = 0; i < 9; ++i)
    {
        double coordinate = 0;
        std::cin >> coordinate;
        if (!std::cin.good())
        {
            std::abort();
        }
        dots_array_1.push_back(coordinate);
    }

    std::vector<double> dots_array_2;
    for (int i = 0; i < 9; ++i)
    {
        double coordinate = 0;
        std::cin >> coordinate;
        if (!std::cin.good())
        {
            std::abort();
        }
        dots_array_2.push_back(coordinate);
    }

    lingeo::Triangle_t T1{dots_array_1};
    lingeo::Triangle_t T2{dots_array_2};

    bool result = intersection_3D_triangles(T1, T2);

    if (result)
    {
        std::cout << "\033[32;1m INTERSECT \033[0m" << std::endl;
    }
    else
    {
        std::cout << "\033[31;1m DOESN'T INTERSECT \033[0m" << std::endl;
    }


}