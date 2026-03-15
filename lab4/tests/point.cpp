#include "point.hpp"

#include <gtest/gtest.h>

TEST(PointTest, DefaultConstructor) {
    Point<int> point;
    EXPECT_EQ(point.x, 0);
    EXPECT_EQ(point.y, 0);
}

TEST(PointTest, ParameterizedConstructor) {
    Point<double> point(3.5, -2.1);
    EXPECT_DOUBLE_EQ(point.x, 3.5);
    EXPECT_DOUBLE_EQ(point.y, -2.1);
}

TEST(PointTest, EqualityOperator) {
    Point<int> point1(1, 2);
    Point<int> point2(1, 2);
    Point<int> point3(2, 3);

    EXPECT_TRUE(point1 == point2);
    EXPECT_FALSE(point1 == point3);
}

TEST(PointTest, InputOperator) {
    std::istringstream iss("10 20");

    Point<int> point;
    iss >> point;

    EXPECT_EQ(point.x, 10);
    EXPECT_EQ(point.y, 20);
}

TEST(PointTest, OutputOperator) {
    Point<int> point(5, 7);

    std::ostringstream oss;
    oss << point;

    EXPECT_EQ(oss.str(), "(5, 7)");
}

TEST(PointTest, FloatingPoint) {
    Point<double> point1(1.1, 2.2);
    Point<double> point2(1.1, 2.2);
    Point<double> point3(3.3, 4.4);

    EXPECT_TRUE(point1 == point2);
    EXPECT_FALSE(point1 == point3);

    std::ostringstream oss;
    oss << point1;
    EXPECT_EQ(oss.str(), "(1.1, 2.2)");
}
