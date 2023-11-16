#include <gtest/gtest.h>
#include "../../include/lingeo.hpp"

TEST(TriangleMain, swap)
{
    Point_t p{0, 4, 0};
    Point_t q{0, 0, 4};
    Point_t r{0, -4, 0};

    lingeo::Triangle_t tr{p, q, r};

    tr.swap_q_r();
    tr.print();
}

TEST(TriangleMain, projectionZYintoXY)
{
    Point_t p{0, 4, 0};
    Point_t q{0, 0, 4};
    Point_t r{0, -4, 0};

    lingeo::Triangle_t tr{p, q, r};

    tr.project_onto_plane();
    tr.print();
}

TEST(TriangleMain, projectionXZintoXY)
{
    Point_t p{-6, 0, 0};
    Point_t q{0, 0, 4};
    Point_t r{4, 0, 0};

    lingeo::Triangle_t tr{p, q, r};

    tr.project_onto_plane();
    tr.print();
}

TEST(TriangleMain, projectionXYintoXY)
{
    Point_t p{-2, 0, 1};
    Point_t q{2, 2, 1};
    Point_t r{0, -2, 1};

    lingeo::Triangle_t tr{p, q, r};

    tr.project_onto_plane();
    tr.print();
}

TEST(TriangleMain, arrange_ctclckws)
{
    Point_t p{-2, 0, 1};
    Point_t q{2, 2, 1};
    Point_t r{0, -2, 1};

    lingeo::Triangle_t tr{p, q, r};

    tr.arrange_counterclockwise();
    tr.print();
}

TEST(TriangleMain, circular_permutation)
{
    Point_t p{-2, 0, 1};
    Point_t q{2, 2, 1};
    Point_t r{0, -2, 1};

    lingeo::Triangle_t tr{p, q, r};

    tr.circular_permutation();
    tr.print();
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}