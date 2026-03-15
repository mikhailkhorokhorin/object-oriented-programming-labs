#include "point.hpp"

#include <gtest/gtest.h>

TEST(PointTest, EqualityOperator) {
    Point point1{1.0, 2.0};
    Point point2{1.0, 2.0};
    Point point3{2.0, 3.0};

    EXPECT_TRUE(point1 == point2);
    EXPECT_FALSE(point1 == point3);
}

TEST(PointTest, InputOperator) {
    std::istringstream input("3.5 4.5");

    Point point;
    input >> point;

    EXPECT_DOUBLE_EQ(point.x, 3.5);
    EXPECT_DOUBLE_EQ(point.y, 4.5);
}

TEST(PointTest, OutputOperator) {
    Point point{1.1, 2.2};

    std::ostringstream output;
    output << point;

    EXPECT_EQ(output.str(), "(1.1, 2.2)");
}

TEST(PointTest, InputOutputConsistency) {
    std::istringstream input("5.5 6.6");

    Point point;
    input >> point;

    std::ostringstream output;
    output << point;

    EXPECT_EQ(output.str(), "(5.5, 6.6)");
}
