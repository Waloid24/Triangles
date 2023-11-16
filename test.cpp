#include <iostream>
#include <vector>
#include <typeinfo>

int main(void)
{
    std::vector<int> int_vec = {1, 2, 3};

    using vec_it = typename std::vector<int>::iterator;

    for (auto it : int_vec)
    {
        std::cout << "typeid(it) = " << typeid(it).name() << std::endl;
    }
}