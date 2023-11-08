#include <gtest/gtest.h>
#include "../../include/double_comparison.hpp"

TEST(MainDoubles, is_equal)
{
    double a = 0.0000001;
    double b = 0.0000002;

    bool rslt = cmp::is_equal(a, b);

    ASSERT_EQ(rslt, true);
}

TEST(MainDoubles, is_0)
{
    double a = 0;

    bool rslt = cmp::is_0(a);

    ASSERT_EQ(rslt, true);
}

TEST(MainDoubles, greater)
{
    double a = 54.000002;
    double b = 54.000001;

    bool rslt = cmp::greater(a, b);

    ASSERT_EQ(rslt, true);
}

TEST(MainDoubles, less)
{
    double a = 54.000001;
    double b = 54.000002;

    bool rslt = cmp::less(a, b);

    ASSERT_EQ(rslt, true);
}

TEST(MainDoubles, greater_equal)
{
    double a = 54.000002;
    double b = 54.000001;

    bool rslt = cmp::greater_equal(a, b);

    ASSERT_EQ(rslt, true);
}

TEST(MainDoubles, less_equal)
{
    double a = 0.00000;
    double b = 0.000002;

    bool rslt = cmp::less_equal(a, b);

    ASSERT_EQ(rslt, true);
}

TEST(MainDoubles, sign)
{
    double a = -54.000002;

    int rslt = cmp::sign(a);

    ASSERT_EQ(rslt, -1);
}




