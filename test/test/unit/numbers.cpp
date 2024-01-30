#include <gtest/gtest.h>
#include "../../include/maths/maths.hpp"

TEST(MainDoubles, is_equal)
{
    double a = 0.0000001;
    double b = 0.0000002;

    bool rslt = maths::is_equal(a, b);

    ASSERT_EQ(rslt, true);
}

TEST(MainDoubles, is_0)
{
    double a = 0;

    bool rslt = maths::is_0(a);

    ASSERT_EQ(rslt, true);
}

TEST(MainDoubles, greater)
{
    double a = 54.000002;
    double b = 54.000001;

    bool rslt = maths::greater(a, b);

    ASSERT_EQ(rslt, true);
}

TEST(MainDoubles, less)
{
    double a = 54.000001;
    double b = 54.000002;

    bool rslt = maths::less(a, b);

    ASSERT_EQ(rslt, true);
}

TEST(MainDoubles, greater_equal)
{
    double a = 54.000002;
    double b = 54.000001;

    bool rslt = maths::greater_equal(a, b);

    ASSERT_EQ(rslt, true);
}

TEST(MainDoubles, less_equal)
{
    double a = 0.00000;
    double b = 0.000002;

    bool rslt = maths::less_equal(a, b);

    ASSERT_EQ(rslt, true);
}

TEST(MainDoubles, sign)
{
    double a = -54.000002;

    int rslt = maths::sign(a);

    ASSERT_EQ(rslt, -1);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


