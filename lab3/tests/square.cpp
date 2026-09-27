#include "square.hpp"

#include <gtest/gtest.h>

#include <cmath>
#include <sstream>
#include <utility>

#include "rectangle.hpp"

TEST(SquareTest, DefaultHasFourZeroPoints) {
    const Square square;
    EXPECT_EQ(square.getSize(), 4U);
    for (const auto& point : square.getPoints()) {
        EXPECT_EQ(point, (Point{0, 0}));
    }
    EXPECT_DOUBLE_EQ(static_cast<double>(square), 0);
    EXPECT_EQ(square.getCenter(), (Point{0, 0}));
}

TEST(SquareTest, AreaAndCenter) {
    const Square square({0, 0}, {2, 0}, {2, 2}, {0, 2});
    EXPECT_DOUBLE_EQ(static_cast<double>(square), 4);
    EXPECT_EQ(square.getCenter(), (Point{1, 1}));
}

TEST(SquareTest, RotatedSquareArea) {
    const Square square({1, 0}, {2, 1}, {1, 2}, {0, 1});
    EXPECT_DOUBLE_EQ(static_cast<double>(square), 2);
}

TEST(SquareTest, ReadAndPrint) {
    Square square;
    std::istringstream in("0 0 1 0 1 1 0 1");
    in >> square;
    std::ostringstream out;
    out << square;
    EXPECT_EQ(out.str(), "(0, 0) (1, 0) (1, 1) (0, 1)");
}

TEST(SquareTest, FailedReadKeepsPoints) {
    Square square({0, 0}, {1, 0}, {1, 1}, {0, 1});
    std::istringstream in("5 5 x");
    in >> square;
    EXPECT_TRUE(in.fail());
    EXPECT_EQ(square.getPoints()[0], (Point{0, 0}));
}

TEST(SquareTest, EqualityIgnoresVertexOrderButNotType) {
    const Square square({0, 0}, {1, 0}, {1, 1}, {0, 1});
    const Square reordered({1, 1}, {0, 1}, {0, 0}, {1, 0});
    const Square other({0, 0}, {2, 0}, {2, 2}, {0, 2});
    const Rectangle sameVertices({0, 0}, {1, 0}, {1, 1}, {0, 1});
    EXPECT_TRUE(square == reordered);
    EXPECT_FALSE(square == other);
    EXPECT_FALSE(square == sameVertices);
}

TEST(SquareTest, CloneIsEqualCopy) {
    const Square square({0, 0}, {1, 0}, {1, 1}, {0, 1});
    const auto clone = square.clone();
    EXPECT_NE(dynamic_cast<Square*>(clone.get()), nullptr);
    EXPECT_TRUE(*clone == square);
}

TEST(SquareTest, MovedFromSquareStaysUsable) {
    Square source({0, 0}, {3, 0}, {3, 3}, {0, 3});
    Square target;
    target = std::move(source);
    EXPECT_DOUBLE_EQ(static_cast<double>(target), 9);
    EXPECT_EQ(source.getSize(), 4U);
    EXPECT_TRUE(std::isfinite(static_cast<double>(source)));
    EXPECT_TRUE(std::isfinite(source.getCenter().x));
    std::ostringstream out;
    out << source;
    EXPECT_FALSE(out.str().empty());
}
