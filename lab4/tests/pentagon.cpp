#include "pentagon.hpp"

#include <gtest/gtest.h>

#include <sstream>

TEST(PentagonTest, DefaultHasFiveVertices) {
    const Pentagon<double> pentagon;
    EXPECT_EQ(pentagon.getSize(), 5U);
    EXPECT_DOUBLE_EQ(pentagon.getArea(), 0.0);
}

TEST(PentagonTest, ShoelaceArea) {
    const Pentagon<int> pentagon({0, 0}, {2, 0}, {3, 2}, {1, 4}, {-1, 2});
    EXPECT_DOUBLE_EQ(pentagon.getArea(), 10.0);
}

TEST(PentagonTest, CenterIsAreaCentroid) {
    const Pentagon<int> pentagon({0, 0}, {2, 0}, {3, 2}, {1, 4}, {-1, 2});
    EXPECT_DOUBLE_EQ(pentagon.getCenter().x, 1.0);
    EXPECT_DOUBLE_EQ(pentagon.getCenter().y, 26.0 / 15.0);
}

TEST(PentagonTest, CenterWithNegativeIntegerCoordinates) {
    const Pentagon<int> pentagon({-2, 0}, {-2, 1}, {-2, 2}, {-2, 3}, {-3, 4});
    EXPECT_DOUBLE_EQ(pentagon.getCenter().x, -7.0 / 3.0);
    EXPECT_DOUBLE_EQ(pentagon.getCenter().y, 7.0 / 3.0);
}

TEST(PentagonTest, DegenerateCenterIsVertexMean) {
    const Pentagon<int> pentagon({0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0});
    EXPECT_EQ(pentagon.getCenter(), (Point<double>{2, 0}));
}

TEST(PentagonTest, ReadAndClone) {
    Pentagon<double> pentagon;
    std::istringstream in("0 0 2 0 3 2 1 4 -1 2");
    in >> pentagon;
    const auto clone = pentagon.clone();
    EXPECT_NE(dynamic_cast<Pentagon<double>*>(clone.get()), nullptr);
    EXPECT_TRUE(*clone == pentagon);
    EXPECT_DOUBLE_EQ(clone->getArea(), 10.0);
}
