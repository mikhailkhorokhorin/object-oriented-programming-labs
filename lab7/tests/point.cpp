#include "point.hpp"

#include "gtest/gtest.h"

TEST(PointTest, ConstructorAndGetters) {
    Point point(3, 4);
    EXPECT_EQ(point.getX(), 3);
    EXPECT_EQ(point.getY(), 4);
}

TEST(PointTest, DistanceTo) {
    Point point1(0, 0);
    Point point2(3, 4);

    double distance1to2 = point1.distanceTo(point2);
    EXPECT_DOUBLE_EQ(distance1to2, 5.0);

    double distance1to1 = point1.distanceTo(point1);
    EXPECT_DOUBLE_EQ(distance1to1, 0.0);

    Point point3(-3, -4);
    double distance2to3 = point2.distanceTo(point3);
    EXPECT_DOUBLE_EQ(distance2to3, 10.0);
}