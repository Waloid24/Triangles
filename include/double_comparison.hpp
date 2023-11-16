#ifndef DOUBLE_COMPARISON_HPP
#define DOUBLE_COMPARISON_HPP

#include <cfloat>
#include <cmath>

namespace cmp {

    constexpr double min_number = 1e-6f;

    bool is_equal(double A, double B,
        double max_diff = min_number, double max_rel_diff = DBL_EPSILON)
    {
        double diff = std::fabs(A - B);
        if (diff < min_number)
            return true;

        return diff < (std::fmax(std::fabs(A), std::fabs(B))*max_rel_diff);
    }

    bool is_0(double A, double max_diff = min_number)
    {
        return std::fabs(A) < max_diff;
    }

    bool greater(double A, double B,
        double max_diff = min_number, double max_rel_diff = min_number)
    {
        return (A > B) && !is_equal(A, B, max_diff, max_rel_diff);
    }

    bool less(double A, double B,
        double max_diff = min_number, double max_rel_diff = min_number)
    {
        return (A < B) && !is_equal(A, B, max_diff, max_rel_diff);
    }

    bool greater_equal(double A, double B,
        double max_diff = min_number, double max_rel_diff = min_number)
    {
        return (A > B) || is_equal(A, B, max_diff, max_rel_diff);
    }

    bool less_equal(double A, double B,
        double max_diff = min_number, double max_rel_diff = min_number)
    {
        return (A < B) || is_equal(A, B, max_diff, max_rel_diff);
    }

    int sign(double val)
    {
        return greater(val, 0) - less(val, 0); 
    }

    double &max(double &l, double &r) //TODO: check for a dead parrot
    {
        if (greater_equal(l, r))
        {
            return l;
        }
        else
        {
            return r;
        }
    }

    int round(double num)
    {
        int tmp = (int)num;
        if (is_equal(tmp, num))
            return tmp;
        else
            return ++tmp;
    }
}

#endif