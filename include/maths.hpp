#ifndef MATHS_HPP
#define MATHS_HPP

namespace maths
{

long long find_largest_pow_of_two(size_t num)
{
    num--;
    num |= num >> 1;
    num |= num >> 2;
    num |= num >> 4;
    num |= num >> 8;
    num |= num >> 16;
    num |= num >> 32;
    num++;
    return num;
}

}

#endif