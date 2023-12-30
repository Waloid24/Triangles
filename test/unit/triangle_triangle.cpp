#include <gtest/gtest.h>
#include "../../include/vector.hpp"
#include "../../include/triangle.hpp"
#include "../../include/double_comparison.hpp"

#if 0
TEST(TriangleTriangle, parallel)
{
    lingeo::Vector3 p1{3, 0, 0};
    lingeo::Vector3 q1{0, 0, 1};
    lingeo::Vector3 r1{0, 3, 0};

    lingeo::Vector3 p2{4, 0, 0};
    lingeo::Vector3 q2{0, 0, 2};
    lingeo::Vector3 r2{0, 4, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    lingeo::position rslt12 = lingeo::triangle_and_plane_intersection(tr1, tr2);
    lingeo::position rslt21 = lingeo::triangle_and_plane_intersection(tr2, tr1);

    EXPECT_EQ(rslt12, lingeo::DOESNT_INTERSECT);   
    EXPECT_EQ(rslt21, lingeo::DOESNT_INTERSECT);   
}

TEST(TriangleTriangle, intersect_on_side)
{
    lingeo::Vector3 p1{2, 2, 0};
    lingeo::Vector3 q1{0, -2, 0};
    lingeo::Vector3 r1{-2, 0, 0};

    lingeo::Vector3 p2{2, 2, 0};
    lingeo::Vector3 q2{0, 6, 0};
    lingeo::Vector3 r2{-2, 0, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, true);   
}

TEST(TriangleTriangle, R1_3_a_intsct)
{
    lingeo::Vector3 p2{0, 0, 0};
    lingeo::Vector3 q2{2, -2, 0};
    lingeo::Vector3 r2{2, 2, 0};

    lingeo::Vector3 p1{0, 4, 0};
    lingeo::Vector3 q1{1, -2, 0};
    lingeo::Vector3 r1{6, 4, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, true);   
}

TEST(TriangleTriangle, R1_4_a_not_intsct)
{
    lingeo::Vector3 p2{0, 0, 0};
    lingeo::Vector3 q2{2, -2, 0};
    lingeo::Vector3 r2{2, 2, 0};

    lingeo::Vector3 p1{0, 4, 0};
    lingeo::Vector3 q1{-2, -2, 0};
    lingeo::Vector3 r1{-1, -1, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, false);   
}

TEST(TriangleTriangle, R1_5_not_intsct)
{
    lingeo::Vector3 p2{0, 0, 0};
    lingeo::Vector3 q2{2, -2, 0};
    lingeo::Vector3 r2{2, 2, 0};

    lingeo::Vector3 p1{-2, 2, 0};
    lingeo::Vector3 q1{0, 1.61, 0};
    lingeo::Vector3 r1{1.2, 8.35, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, false);   
}

TEST(TriangleTriangle, R1_5_intsct)
{
    lingeo::Vector3 p2{0, 0, 0};
    lingeo::Vector3 q2{2, -2, 0};
    lingeo::Vector3 r2{2, 2, 0};

    lingeo::Vector3 p1{-2, 2, 0};
    lingeo::Vector3 q1{0, -2.08, 0};
    lingeo::Vector3 r1{1.2, 4.66, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, false);   
}

TEST(TriangleTriangle, R1_2_a_not_intsct)
{
    lingeo::Vector3 p2{0, 0, 0};
    lingeo::Vector3 q2{2, -2, 0};
    lingeo::Vector3 r2{2, 2, 0};

    lingeo::Vector3 p1{-1.49, 2.33, 0};
    lingeo::Vector3 q1{-2, 1, 0};
    lingeo::Vector3 r1{-1, -1, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, false);   
}

TEST(TriangleTriangle, R1_3_b_not_intsct)
{
    lingeo::Vector3 p2{0, 0, 0};
    lingeo::Vector3 q2{2, -2, 0};
    lingeo::Vector3 r2{2, 2, 0};

    lingeo::Vector3 p1{-1.49, 2.33, 0};
    lingeo::Vector3 q1{-2, 1, 0};
    lingeo::Vector3 r1{2.42, 2.46, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, false);   
}

TEST(TriangleTriangle, R1_4_b_not_intsct)
{
    lingeo::Vector3 p2{0, 0, 0};
    lingeo::Vector3 q2{2, -2, 0};
    lingeo::Vector3 r2{2, 2, 0};

    lingeo::Vector3 p1{-1.49, 2.33, 0};
    lingeo::Vector3 q1{-2, 1, 0};
    lingeo::Vector3 r1{0.12, -0.51, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, false);   
}

TEST(TriangleTriangle, R2_4_a_intsct)
{
    lingeo::Vector3 p2{0, 0, 0};
    lingeo::Vector3 q2{2, -2, 0};
    lingeo::Vector3 r2{2, 1, 0};

    lingeo::Vector3 p1{2.75, 3.00, 0};
    lingeo::Vector3 q1{2, -2, 0};
    lingeo::Vector3 r1{1.94, -2.42, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, true);   
}

TEST(TriangleTriangle, R2_4_a_not_intsct)
{
    lingeo::Vector3 p2{0, 0, 0};
    lingeo::Vector3 q2{2, -2, 0};
    lingeo::Vector3 r2{2, 1, 0};

    lingeo::Vector3 p1{2.75, 3.00, 0};
    lingeo::Vector3 q1{1.94, -2.42, 0};
    lingeo::Vector3 r1{2.1, -2.67, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, false);   
}

TEST(TriangleTriangle, R2_4_b_not_intsct)
{
    lingeo::Vector3 p2{0, 0, 0};
    lingeo::Vector3 q2{2, -2, 0};
    lingeo::Vector3 r2{2, 1, 0};

    lingeo::Vector3 p1{2.75, 3.00, 0};
    lingeo::Vector3 q1{-1.58, -1.32, 0};
    lingeo::Vector3 r1{-0.91, -0.81, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, false);   
}

TEST(TriangleTriangle, R2_5_a_intsct)
{
    lingeo::Vector3 p2{0, 0, 0};
    lingeo::Vector3 q2{2, -2, 0};
    lingeo::Vector3 r2{2, 1, 0};

    lingeo::Vector3 p1{2.75, 3.00, 0};
    lingeo::Vector3 q1{-1.58, -1.32, 0};
    lingeo::Vector3 r1{2.94, 1.47, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, true);   
}

TEST(TriangleTriangle, R2_5_a_not_intsct)
{
    lingeo::Vector3 p2{0, 0, 0};
    lingeo::Vector3 q2{2, -2, 0};
    lingeo::Vector3 r2{2, 1, 0};

    lingeo::Vector3 p1{2.75, 3.00, 0};
    lingeo::Vector3 q1{-1.58, -1.32, 0};
    lingeo::Vector3 r1{1.9, 1.47, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, false);   
}

TEST(TriangleTriangle, R2_3_b_not_intsct)
{
    lingeo::Vector3 p2{0, 0, 0};
    lingeo::Vector3 q2{2, -2, 0};
    lingeo::Vector3 r2{2, 1, 0};

    lingeo::Vector3 p1{2.75, 3.00, 0};
    lingeo::Vector3 q1{2.94, 1.47, 0};;
    lingeo::Vector3 r1{4, 0, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, false);   
}

TEST(TriangleTriangle, R2_4_c_not_intsct)
{
    lingeo::Vector3 p2{0, 0, 0};
    lingeo::Vector3 q2{2, -2, 0};
    lingeo::Vector3 r2{2, 1, 0};

    lingeo::Vector3 p1{2.75, 3.00, 0};
    lingeo::Vector3 q1{2.38, 0.55, 0};;
    lingeo::Vector3 r1{2.2, 1.1, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, false);   
}

TEST(TriangleTriangle, R2_5_b_intsct)
{
    lingeo::Vector3 p2{0, 0, 0};
    lingeo::Vector3 q2{2, -2, 0};
    lingeo::Vector3 r2{2, 1, 0};

    lingeo::Vector3 p1{2.75, 3.00, 0};
    lingeo::Vector3 r1{2.2, 1.1, 0};
    lingeo::Vector3 q1{1.78, -2.85, 0};;

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, true);   
}

TEST(TriangleTriangle, R2_5_b_not_intsct)
{
    lingeo::Vector3 p2{0, 0, 0};
    lingeo::Vector3 q2{2, -2, 0};
    lingeo::Vector3 r2{2, 1, 0};

    lingeo::Vector3 p1{2.75, 3.00, 0};
    lingeo::Vector3 r1{2.36, 1.18, 0};
    lingeo::Vector3 q1{1.58, -7.02, 0};;

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, false);   
}

TEST(TriangleTriangle, R2_2_b_not_intsct)
{
    lingeo::Vector3 p2{0, 0, 0};
    lingeo::Vector3 q2{2, -2, 0};
    lingeo::Vector3 r2{2, 1, 0};

    lingeo::Vector3 p1{2.75, 3.00, 0};
    lingeo::Vector3 r1{0.4, 2.61, 0};
    lingeo::Vector3 q1{-0.67, 0.2, 0};;

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, false);   
}

TEST(TriangleTriangle, R2_4_d_not_intsct)
{
    lingeo::Vector3 p2{0, 0, 0};
    lingeo::Vector3 q2{2, -2, 0};
    lingeo::Vector3 r2{2, 1, 0};

    lingeo::Vector3 p1{2.75, 3.00, 0};
    lingeo::Vector3 r1{-5.58, -4.17, 0};
    lingeo::Vector3 q1{0.26, 1.68, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, false);   
}

TEST(TriangleTriangle, R2_4_d_intsct)
{
    lingeo::Vector3 p2{0, 0, 0};
    lingeo::Vector3 q2{2, -2, 0};
    lingeo::Vector3 r2{2, 1, 0};

    lingeo::Vector3 p1{2.75, 3.00, 0};
    lingeo::Vector3 r1{2.63, -2.08, 0};
    lingeo::Vector3 q1{0.26, 1.68, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, true);   
}

TEST(TriangleTriangle, R2_4_e_not_intsct)
{
    lingeo::Vector3 p2{0, 0, 0};
    lingeo::Vector3 q2{2, -2, 0};
    lingeo::Vector3 r2{2, 1, 0};

    lingeo::Vector3 p1{2.75, 3.00, 0};
    lingeo::Vector3 r1{2.06, 2.17, 0};
    lingeo::Vector3 q1{3.22, -1.51, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, false);   
}

TEST(TriangleTriangle, R2_5_c_not_intsct)
{
    lingeo::Vector3 p2{0, 0, 0};
    lingeo::Vector3 q2{2, -2, 0};
    lingeo::Vector3 r2{2, 1, 0};

    lingeo::Vector3 p1{2.75, 3.00, 0};
    lingeo::Vector3 r1{1.73, -2.52, 0};
    lingeo::Vector3 q1{2.44, 2.25, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, true);   
}
#endif

TEST(TriangleTriangle, R1_4_b_intsct)
{
    lingeo::Vector3 p2{0, 0, 0};
    lingeo::Vector3 q2{2, -2, 0};
    lingeo::Vector3 r2{2, 2, 0};

    lingeo::Vector3 p1{-1.49, 2.33, 0};
    lingeo::Vector3 q1{-2, 1, 0};
    lingeo::Vector3 r1{0.14, -0.22, 0};

    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    bool rslt = lingeo::triangles_intersection(tr1, tr2);

    EXPECT_EQ(rslt, false);   
}

TEST(TriangleTriangle, mustnt_be_inters_1)
{
    lingeo::Vector3 p1{29.3505, 805.295, 397.635};
    lingeo::Vector3 q1{-248.565, -404.623, -873.618};
    lingeo::Vector3 r1{-386.796, -76.4378, -878.078};

    lingeo::Vector3 p2{-120.028, -992.064, 12.6612};
    lingeo::Vector3 q2{-729.661, -244.151, -979.961};
    lingeo::Vector3 r2{997.444, 982.96, -259.114};

    //29.3505 805.295 397.635 -248.565 -404.623 -873.618 -386.796 -76.4378 -878.078 -120.028 -992.064 12.6612 -729.661 -244.151 -979.961 997.444 982.96 -259.114
    //2.93505 80.5295 39.7635 -24.8565 -40.4623 -87.3618 -38.6796 -7.64378 -87.8078 -12.0028 -99.2064 1.26612 -72.9661 -24.4151 -97.9961 99.7444 98.296 -25.9114
    double loc = determ(p2, q2, r2, p1);
    lingeo::Triangle tr1{p1, q1, r1};
    lingeo::Triangle tr2{p2, q2, r2};

    tr1.print();
    tr2.print();

    auto P_loc1 = get_point_location(p2, q2, r2, p1);
    auto Q_loc1 = get_point_location(p2, q2, r2, q1);
    auto R_loc1 = get_point_location(p2, q2, r2, r1);

    auto P_loc2 = get_point_location(p1, q1, r1, p2);
    auto Q_loc2 = get_point_location(p1, q1, r1, q2);
    auto R_loc2 = get_point_location(p1, q1, r1, r2);

    std::cout << P_loc1 << ' ' << Q_loc1 << ' ' << R_loc1 << std::endl;
    std::cout << P_loc2 << ' ' << Q_loc2 << ' ' << R_loc2 << std::endl;

    #if 1
    bool rslt = lingeo::triangles_intersection(tr1, tr2);
    EXPECT_EQ(rslt, true);
    #endif
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

