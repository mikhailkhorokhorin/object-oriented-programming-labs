#include "point.hpp"

#include <gtest/gtest.h>

TEST(PointTest, DefaultIsOrigin) {
    const Point point;
    EXPECT_EQ(point.getX(), 0);
    EXPECT_EQ(point.getY(), 0);
}

TEST(PointTest, Distance) {
    EXPECT_DOUBLE_EQ(Point(0, 0).distanceTo(Point(3, 4)), 5.0);
    EXPECT_DOUBLE_EQ(Point(-1, -1).distanceTo(Point(-1, -1)), 0.0);
}

TEST(PointTest, Equality) {
    EXPECT_EQ(Point(1, 2), Point(1, 2));
    EXPECT_NE(Point(1, 2), Point(2, 1));
}
