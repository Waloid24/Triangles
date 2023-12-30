#include <gtest/gtest.h>
#include "../../include/lingeo.hpp"

TEST(TriangleMain, swap)
{
    Vector_3D p{0, 4, 0};
    Vector_3D q{0, 0, 4};
    Vector_3D r{0, -4, 0};

    lingeo::Triangle tr{p, q, r};

    tr.swap_q_r();
    tr.print();
}

TEST(TriangleMain, projectionZYintoXY)
{
    Vector_3D p{0, 4, 0};
    Vector_3D q{0, 0, 4};
    Vector_3D r{0, -4, 0};

    lingeo::Triangle tr{p, q, r};

    tr.project_onto_plane();
    tr.print();
}

TEST(TriangleMain, projectionXZintoXY)
{
    Vector_3D p{-6, 0, 0};
    Vector_3D q{0, 0, 4};
    Vector_3D r{4, 0, 0};

    lingeo::Triangle tr{p, q, r};

    tr.project_onto_plane();
    tr.print();
}

TEST(TriangleMain, projectionXYintoXY)
{
    Vector_3D p{-2, 0, 1};
    Vector_3D q{2, 2, 1};
    Vector_3D r{0, -2, 1};

    lingeo::Triangle tr{p, q, r};

    tr.project_onto_plane();
    tr.print();
}

TEST(TriangleMain, arrange_ctclckws)
{
    Vector_3D p{-2, 0, 1};
    Vector_3D q{2, 2, 1};
    Vector_3D r{0, -2, 1};

    lingeo::Triangle tr{p, q, r};

    tr.arrange_counterclockwise();
    tr.print();
}

TEST(TriangleMain, circular_permutation)
{
    Vector_3D p{-2, 0, 1};
    Vector_3D q{2, 2, 1};
    Vector_3D r{0, -2, 1};

    lingeo::Triangle tr{p, q, r};

    tr.circular_permutation();
    tr.print();
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}