#include "hexagon.hpp"

#include <gtest/gtest.h>

#include <sstream>

TEST(HexagonTest, DefaultHasSixVertices) {
    const Hexagon<int> hexagon;
    EXPECT_EQ(hexagon.getSize(), 6U);
}

TEST(HexagonTest, ShoelaceAreaAndCenter) {
    const Hexagon<double> hexagon({0, 0}, {2, 0}, {3, 1}, {2, 2}, {0, 2}, {-1, 1});
    EXPECT_DOUBLE_EQ(hexagon.getArea(), 6.0);
    EXPECT_EQ(hexagon.getCenter(), (Point<double>{1, 1}));
}

TEST(HexagonTest, Print) {
    const Hexagon<int> hexagon({0, 0}, {2, 0}, {3, 1}, {2, 2}, {0, 2}, {-1, 1});
    std::ostringstream out;
    hexagon.print(out);
    EXPECT_EQ(out.str(), "(0, 0) (2, 0) (3, 1) (2, 2) (0, 2) (-1, 1)");
}

TEST(HexagonTest, Clone) {
    const Hexagon<int> hexagon({0, 0}, {2, 0}, {3, 1}, {2, 2}, {0, 2}, {-1, 1});
    const auto clone = hexagon.clone();
    EXPECT_NE(dynamic_cast<Hexagon<int>*>(clone.get()), nullptr);
    EXPECT_TRUE(*clone == hexagon);
}
