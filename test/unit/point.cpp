#include <gtest/gtest.h>
#include "../../include/lingeo.hpp"

struct PointMain : public testing::Test {
    Vector3 *p;
    Vector3 *q;
    Vector3 *r;

    void SetUp() { 
        p = new Vector3{0, 4, 0};
        q = new Vector3{0, 0, 4};
        r = new Vector3{0, -4, 0};
    }
    void TearDown() {
        delete p;
        delete q;
        delete r;
    }
};

TEST_F(PointMain, projections)
{
    p->project_onto_XY();
    q->project_onto_XY();
    r->project_onto_XY();

    p->print();
    q->print();
    r->print();

    ASSERT_EQ(p->z(), 0);
    ASSERT_EQ(q->z(), 0);
    ASSERT_EQ(r->z(), 0);

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}