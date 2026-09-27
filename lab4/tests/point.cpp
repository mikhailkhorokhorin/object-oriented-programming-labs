#include "point.hpp"

#include <gtest/gtest.h>

#include <sstream>

TEST(PointTest, DefaultIsOrigin) {
    const Point<int> point;
    EXPECT_EQ(point.x, 0);
    EXPECT_EQ(point.y, 0);
}

TEST(PointTest, Equality) {
    EXPECT_TRUE((Point<int>{1, 2} == Point<int>{1, 2}));
    EXPECT_FALSE((Point<int>{1, 2} == Point<int>{2, 1}));
    EXPECT_TRUE((Point<double>{1.5, -2.5} == Point<double>{1.5, -2.5}));
}

TEST(PointTest, StreamRoundTrip) {
    std::istringstream in("10 -20");
    Point<int> point;
    in >> point;
    EXPECT_EQ(point, (Point<int>{10, -20}));
    std::ostringstream out;
    out << point << ";" << Point<double>{1.1, 2.2};
    EXPECT_EQ(out.str(), "(10, -20);(1.1, 2.2)");
}
