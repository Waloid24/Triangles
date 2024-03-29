#ifndef MATHS_HPP
#define MATHS_HPP

#include <cfloat>
#include <cmath>
#include <utility>

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

    static constexpr double min_number_ = 1e-6f;

    bool is_equal(double A, double B,
        double max_diff = min_number_, double max_rel_diff = min_number_)
    {
        double diff = std::fabs(A - B);
        if (diff < min_number_)
            return true;

        return diff < (std::fmax(std::fabs(A), std::fabs(B))*max_rel_diff);
    }

    bool is_0(double A, double max_diff = min_number_)
    {
        return std::fabs(A) < max_diff;
    }

    bool greater(double A, double B,
        double max_diff = min_number_, double max_rel_diff = min_number_)
    {
        return (A > B) && !is_equal(A, B, max_diff, max_rel_diff);
    }

    bool less(double A, double B,
        double max_diff = min_number_, double max_rel_diff = min_number_)
    {
        return (A < B) && !is_equal(A, B, max_diff, max_rel_diff);
    }

    bool greater_equal(double A, double B,
        double max_diff = min_number_, double max_rel_diff = min_number_)
    {
        return (A > B) || is_equal(A, B, max_diff, max_rel_diff);
    }

    bool less_equal(double A, double B,
        double max_diff = min_number_, double max_rel_diff = min_number_)
    {
        return (A < B) || is_equal(A, B, max_diff, max_rel_diff);
    }

    int sign(double val)
    {
        return greater(val, 0) - less(val, 0); 
    }

    double &max(double &l, double &r) // есть std::max, который принимает компаратор
    {
        if (greater_equal(l, r))
            return l;
        else
            return r;
    }

    double &min(double &l, double &r)
    {
        if (less_equal(l, r))
            return l;
        else
            return r;
    }

    std::pair<double, double> max_min(double l, double r)
    {
        if (greater_equal(l,r))
            return std::pair<double, double>(l,r);
        else
            return std::pair<double, double>(r,l);
    }

    long long round(double num)
    {
        long long tmp = static_cast<long long>(num);
        if (is_equal(tmp, num))
            return tmp;
        else
            return ++tmp;
    }

}

#endif