#include <gtest/gtest.h>
#include "../../include/intersections/intersection_driver.hpp"

TEST(TriangleMain, swap)
{
    lingeo::Vector p{0, 4, 0};
    lingeo::Vector q{0, 0, 4};
    lingeo::Vector r{0, -4, 0};

    lingeo::Triangle tr{p, q, r};

    tr.swap_q_r();
    tr.print();
}

TEST(TriangleMain, projectionZYintoXY)
{
    lingeo::Vector p{0, 4, 0};
    lingeo::Vector q{0, 0, 4};
    lingeo::Vector r{0, -4, 0};

    lingeo::Triangle tr{p, q, r};

    lingeo::Triangle tr1 = project_onto_plane(tr, projection_plane(tr));
    tr1.print();
}

TEST(TriangleMain, projectionXZintoXY)
{
    lingeo::Vector p{-6, 0, 0};
    lingeo::Vector q{0, 0, 4};
    lingeo::Vector r{4, 0, 0};

    lingeo::Triangle tr{p, q, r};

    lingeo::Triangle tr1 = project_onto_plane(tr, projection_plane(tr));
    tr1.print();
}

TEST(TriangleMain, projectionXYintoXY)
{
    lingeo::Vector p{-2, 0, 1};
    lingeo::Vector q{2, 2, 1};
    lingeo::Vector r{0, -2, 1};

    lingeo::Triangle tr{p, q, r};

    lingeo::Triangle tr1 = project_onto_plane(tr, projection_plane(tr));
    tr1.print();
}

TEST(TriangleMain, arrange_ctclckws)
{
    lingeo::Vector p{-2, 0, 1};
    lingeo::Vector q{2, 2, 1};
    lingeo::Vector r{0, -2, 1};

    lingeo::Triangle tr{p, q, r};

    tr.arrange_counterclockwise();
    tr.print();
}

TEST(TriangleMain, circular_permutation)
{
    lingeo::Vector p{-2, 0, 1};
    lingeo::Vector q{2, 2, 1};
    lingeo::Vector r{0, -2, 1};

    lingeo::Triangle tr{p, q, r};

    tr.circular_permutation();
    tr.print();
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}