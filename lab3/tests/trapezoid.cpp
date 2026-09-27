#include "trapezoid.hpp"

#include <gtest/gtest.h>

#include <sstream>

TEST(TrapezoidTest, AreaAndCenter) {
    const Trapezoid trapezoid({0, 0}, {4, 0}, {3, 2}, {1, 2});
    EXPECT_DOUBLE_EQ(static_cast<double>(trapezoid), 6);
    EXPECT_DOUBLE_EQ(trapezoid.getCenter().x, 2);
    EXPECT_DOUBLE_EQ(trapezoid.getCenter().y, 8.0 / 9.0);
}

TEST(TrapezoidTest, AreaWithVerticalBases) {
    const Trapezoid trapezoid({0, 0}, {0, 4}, {-2, 3}, {-2, 1});
    EXPECT_DOUBLE_EQ(static_cast<double>(trapezoid), 6);
    EXPECT_DOUBLE_EQ(trapezoid.getCenter().x, -8.0 / 9.0);
    EXPECT_DOUBLE_EQ(trapezoid.getCenter().y, 2);
}

TEST(TrapezoidTest, ReadAndCompare) {
    Trapezoid trapezoid;
    std::istringstream in("0 0 2 0 3 2 1 2");
    in >> trapezoid;
    EXPECT_TRUE(trapezoid == Trapezoid({0, 0}, {2, 0}, {3, 2}, {1, 2}));
    EXPECT_DOUBLE_EQ(static_cast<double>(trapezoid), 4);
}

TEST(TrapezoidTest, Clone) {
    const Trapezoid trapezoid({0, 0}, {4, 0}, {3, 2}, {1, 2});
    const auto clone = trapezoid.clone();
    EXPECT_NE(dynamic_cast<Trapezoid*>(clone.get()), nullptr);
    EXPECT_TRUE(*clone == trapezoid);
}
