#include <gtest/gtest.h>
#include "../../include/primitives/vector.hpp"
#include "../../include/primitives/triangle.hpp"
#include "../../include/maths/maths.hpp"
#include "../../include/intersections/intersection_driver.hpp"

#if 0
TEST(TriangleTriangle, parallel)
{
    lingeo::Vector p1{3, 0, 0};
    lingeo::Vector q1{0, 0, 1};
    lingeo::Vector r1{0, 3, 0};

    lingeo::Vector p2{4, 0, 0};
    lingeo::Vector q2{0, 0, 2};
    lingeo::Vector r2{0, 4, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    lingeo::Triangle_Position rslt12 = lingeo::triangle_and_plane_intersection(tr1, tr2);
    lingeo::Triangle_Position rslt21 = lingeo::triangle_and_plane_intersection(tr2, tr1);

    EXPECT_EQ(rslt12, lingeo::Triangle_Position::DOESNT_INTERSECT);   
    EXPECT_EQ(rslt21, lingeo::Triangle_Position::DOESNT_INTERSECT);   
}

TEST(TriangleTriangle, intersect_on_side)
{
    lingeo::Vector p1{2, 2, 0};
    lingeo::Vector q1{0, -2, 0};
    lingeo::Vector r1{-2, 0, 0};

    lingeo::Vector p2{2, 2, 0};
    lingeo::Vector q2{0, 6, 0};
    lingeo::Vector r2{-2, 0, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, true);   
}

TEST(TriangleTriangle, R1_3_a_intsct)
{
    lingeo::Vector p2{0, 0, 0};
    lingeo::Vector q2{2, -2, 0};
    lingeo::Vector r2{2, 2, 0};

    lingeo::Vector p1{0, 4, 0};
    lingeo::Vector q1{1, -2, 0};
    lingeo::Vector r1{6, 4, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, true);   
}

TEST(TriangleTriangle, R1_4_a_not_intsct)
{
    lingeo::Vector p2{0, 0, 0};
    lingeo::Vector q2{2, -2, 0};
    lingeo::Vector r2{2, 2, 0};

    lingeo::Vector p1{0, 4, 0};
    lingeo::Vector q1{-2, -2, 0};
    lingeo::Vector r1{-1, -1, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, false);   
}

TEST(TriangleTriangle, R1_5_not_intsct)
{
    lingeo::Vector p2{0, 0, 0};
    lingeo::Vector q2{2, -2, 0};
    lingeo::Vector r2{2, 2, 0};

    lingeo::Vector p1{-2, 2, 0};
    lingeo::Vector q1{0, 1.61, 0};
    lingeo::Vector r1{1.2, 8.35, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, false);   
}

TEST(TriangleTriangle, R1_5_intsct)
{
    lingeo::Vector p2{0, 0, 0};
    lingeo::Vector q2{2, -2, 0};
    lingeo::Vector r2{2, 2, 0};

    lingeo::Vector p1{-2, 2, 0};
    lingeo::Vector q1{0, -2.08, 0};
    lingeo::Vector r1{1.2, 4.66, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, false);   
}

TEST(TriangleTriangle, R1_2_a_not_intsct)
{
    lingeo::Vector p2{0, 0, 0};
    lingeo::Vector q2{2, -2, 0};
    lingeo::Vector r2{2, 2, 0};

    lingeo::Vector p1{-1.49, 2.33, 0};
    lingeo::Vector q1{-2, 1, 0};
    lingeo::Vector r1{-1, -1, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, false);   
}

TEST(TriangleTriangle, R1_3_b_not_intsct)
{
    lingeo::Vector p2{0, 0, 0};
    lingeo::Vector q2{2, -2, 0};
    lingeo::Vector r2{2, 2, 0};

    lingeo::Vector p1{-1.49, 2.33, 0};
    lingeo::Vector q1{-2, 1, 0};
    lingeo::Vector r1{2.42, 2.46, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, false);   
}

TEST(TriangleTriangle, R1_4_b_not_intsct)
{
    lingeo::Vector p2{0, 0, 0};
    lingeo::Vector q2{2, -2, 0};
    lingeo::Vector r2{2, 2, 0};

    lingeo::Vector p1{-1.49, 2.33, 0};
    lingeo::Vector q1{-2, 1, 0};
    lingeo::Vector r1{0.12, -0.51, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, false);   
}
#endif

TEST(TriangleTriangle, R2_4_a_intsct)
{
    lingeo::Vector p2{0, 0, 0};
    lingeo::Vector q2{2, -2, 0};
    lingeo::Vector r2{2, 1, 0};

    lingeo::Vector p1{2.75, 3.00, 0};
    lingeo::Vector q1{2, -2, 0};
    lingeo::Vector r1{1.94, -2.42, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, true);   
}

TEST(TriangleTriangle, R2_4_a_not_intsct)
{
    lingeo::Vector p2{0, 0, 0};
    lingeo::Vector q2{2, -2, 0};
    lingeo::Vector r2{2, 1, 0};

    lingeo::Vector p1{2.75, 3.00, 0};
    lingeo::Vector q1{1.94, -2.42, 0};
    lingeo::Vector r1{2.1, -2.67, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, false);   
}

#if 0
TEST(TriangleTriangle, R2_4_b_not_intsct)
{
    lingeo::Vector p2{0, 0, 0};
    lingeo::Vector q2{2, -2, 0};
    lingeo::Vector r2{2, 1, 0};

    lingeo::Vector p1{2.75, 3.00, 0};
    lingeo::Vector q1{-1.58, -1.32, 0};
    lingeo::Vector r1{-0.91, -0.81, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, false);   
}

TEST(TriangleTriangle, R2_5_a_intsct)
{
    lingeo::Vector p2{0, 0, 0};
    lingeo::Vector q2{2, -2, 0};
    lingeo::Vector r2{2, 1, 0};

    lingeo::Vector p1{2.75, 3.00, 0};
    lingeo::Vector q1{-1.58, -1.32, 0};
    lingeo::Vector r1{2.94, 1.47, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, true);   
}

TEST(TriangleTriangle, R2_5_a_not_intsct)
{
    lingeo::Vector p2{0, 0, 0};
    lingeo::Vector q2{2, -2, 0};
    lingeo::Vector r2{2, 1, 0};

    lingeo::Vector p1{2.75, 3.00, 0};
    lingeo::Vector q1{-1.58, -1.32, 0};
    lingeo::Vector r1{1.9, 1.47, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, false);   
}

TEST(TriangleTriangle, R2_3_b_not_intsct)
{
    lingeo::Vector p2{0, 0, 0};
    lingeo::Vector q2{2, -2, 0};
    lingeo::Vector r2{2, 1, 0};

    lingeo::Vector p1{2.75, 3.00, 0};
    lingeo::Vector q1{2.94, 1.47, 0};;
    lingeo::Vector r1{4, 0, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, false);   
}

TEST(TriangleTriangle, R2_4_c_not_intsct)
{
    lingeo::Vector p2{0, 0, 0};
    lingeo::Vector q2{2, -2, 0};
    lingeo::Vector r2{2, 1, 0};

    lingeo::Vector p1{2.75, 3.00, 0};
    lingeo::Vector q1{2.38, 0.55, 0};;
    lingeo::Vector r1{2.2, 1.1, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, false);   
}

TEST(TriangleTriangle, R2_5_b_intsct)
{
    lingeo::Vector p2{0, 0, 0};
    lingeo::Vector q2{2, -2, 0};
    lingeo::Vector r2{2, 1, 0};

    lingeo::Vector p1{2.75, 3.00, 0};
    lingeo::Vector r1{2.2, 1.1, 0};
    lingeo::Vector q1{1.78, -2.85, 0};;

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, true);   
}

TEST(TriangleTriangle, R2_5_b_not_intsct)
{
    lingeo::Vector p2{0, 0, 0};
    lingeo::Vector q2{2, -2, 0};
    lingeo::Vector r2{2, 1, 0};

    lingeo::Vector p1{2.75, 3.00, 0};
    lingeo::Vector r1{2.36, 1.18, 0};
    lingeo::Vector q1{1.58, -7.02, 0};;

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, false);   
}

TEST(TriangleTriangle, R2_2_b_not_intsct)
{
    lingeo::Vector p2{0, 0, 0};
    lingeo::Vector q2{2, -2, 0};
    lingeo::Vector r2{2, 1, 0};

    lingeo::Vector p1{2.75, 3.00, 0};
    lingeo::Vector r1{0.4, 2.61, 0};
    lingeo::Vector q1{-0.67, 0.2, 0};;

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, false);   
}

TEST(TriangleTriangle, R2_4_d_not_intsct)
{
    lingeo::Vector p2{0, 0, 0};
    lingeo::Vector q2{2, -2, 0};
    lingeo::Vector r2{2, 1, 0};

    lingeo::Vector p1{2.75, 3.00, 0};
    lingeo::Vector r1{-5.58, -4.17, 0};
    lingeo::Vector q1{0.26, 1.68, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, false);   
}

TEST(TriangleTriangle, R2_4_d_intsct)
{
    lingeo::Vector p2{0, 0, 0};
    lingeo::Vector q2{2, -2, 0};
    lingeo::Vector r2{2, 1, 0};

    lingeo::Vector p1{2.75, 3.00, 0};
    lingeo::Vector r1{2.63, -2.08, 0};
    lingeo::Vector q1{0.26, 1.68, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, true);   
}

TEST(TriangleTriangle, R2_4_e_not_intsct)
{
    lingeo::Vector p2{0, 0, 0};
    lingeo::Vector q2{2, -2, 0};
    lingeo::Vector r2{2, 1, 0};

    lingeo::Vector p1{2.75, 3.00, 0};
    lingeo::Vector r1{2.06, 2.17, 0};
    lingeo::Vector q1{3.22, -1.51, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, false);   
}

TEST(TriangleTriangle, R2_5_c_not_intsct)
{
    lingeo::Vector p2{0, 0, 0};
    lingeo::Vector q2{2, -2, 0};
    lingeo::Vector r2{2, 1, 0};

    lingeo::Vector p1{2.75, 3.00, 0};
    lingeo::Vector r1{1.73, -2.52, 0};
    lingeo::Vector q1{2.44, 2.25, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, true);   
}


TEST(TriangleTriangle, R1_4_b_intsct)
{
    lingeo::Vector p2{0, 0, 0};
    lingeo::Vector q2{2, -2, 0};
    lingeo::Vector r2{2, 2, 0};

    lingeo::Vector p1{-1.49, 2.33, 0};
    lingeo::Vector q1{-2, 1, 0};
    lingeo::Vector r1{0.14, -0.22, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, false);   
}
#endif

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

