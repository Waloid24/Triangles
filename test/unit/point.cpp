#include <gtest/gtest.h>
#include "../../include/lingeo.hpp"

struct PointMain : public testing::Test {
    lingeo::Point_t *p;
    lingeo::Point_t *q;
    lingeo::Point_t *r;

    void SetUp() { 
        p = new lingeo::Point_t{0, 4, 0};
        q = new lingeo::Point_t{0, 0, 4};
        r = new lingeo::Point_t{0, -4, 0};
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