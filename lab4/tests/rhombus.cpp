#include "rhombus.hpp"

#include <gtest/gtest.h>

#include <sstream>
#include <utility>

#include "pentagon.hpp"

TEST(RhombusTest, DefaultHasFourVertices) {
    const Rhombus<int> rhombus;
    EXPECT_EQ(rhombus.getSize(), 4U);
    EXPECT_DOUBLE_EQ(rhombus.getArea(), 0.0);
    EXPECT_TRUE(rhombus == Rhombus<int>());
}

TEST(RhombusTest, StoresVerticesInOrder) {
    const Rhombus<int> rhombus({0, 0}, {2, 1}, {0, 2}, {-2, 1});
    const Point<int>* points = rhombus.getPoints();
    EXPECT_EQ(points[0], (Point<int>{0, 0}));
    EXPECT_EQ(points[3], (Point<int>{-2, 1}));
}

TEST(RhombusTest, AreaFromDiagonals) {
    const Rhombus<double> rhombus({0, 0}, {2, 1}, {0, 2}, {-2, 1});
    EXPECT_DOUBLE_EQ(rhombus.getArea(), 4.0);
    EXPECT_DOUBLE_EQ(static_cast<double>(rhombus), 4.0);
}

TEST(RhombusTest, IntegerAreaIsNotTruncated) {
    const Rhombus<int> rhombus({0, 0}, {2, 1}, {3, 3}, {1, 2});
    EXPECT_NEAR(rhombus.getArea(), 3.0, 1e-9);
}

TEST(RhombusTest, CenterWithNegativeIntegerCoordinates) {
    const Rhombus<int> rhombus({-4, 0}, {-2, 1}, {-4, 2}, {-6, 1});
    EXPECT_EQ(rhombus.getCenter(), (Point<double>{-4, 1}));
}

TEST(RhombusTest, PrintAndRead) {
    Rhombus<int> rhombus;
    std::istringstream in("0 0 2 1 0 2 -2 1");
    in >> rhombus;
    std::ostringstream out;
    out << rhombus;
    EXPECT_EQ(out.str(), "(0, 0) (2, 1) (0, 2) (-2, 1)");
}

TEST(RhombusTest, FailedReadKeepsVertices) {
    Rhombus<int> rhombus({0, 0}, {2, 1}, {0, 2}, {-2, 1});
    std::istringstream in("1 1 2");
    rhombus.read(in);
    EXPECT_EQ(rhombus.getPoints()[0], (Point<int>{0, 0}));
}

TEST(RhombusTest, EqualityChecksTypeSizeAndVertices) {
    const Rhombus<int> rhombus({0, 0}, {2, 1}, {0, 2}, {-2, 1});
    const Rhombus<int> shifted({1, 0}, {3, 1}, {1, 2}, {-1, 1});
    const Pentagon<int> pentagon;
    EXPECT_TRUE(rhombus == Rhombus<int>(rhombus));
    EXPECT_FALSE(rhombus == shifted);
    EXPECT_FALSE(rhombus == pentagon);
    EXPECT_FALSE(pentagon == rhombus);
}

TEST(RhombusTest, EqualityWithMovedFromRhombus) {
    Rhombus<int> source({0, 0}, {2, 1}, {0, 2}, {-2, 1});
    const Rhombus<int> moved(std::move(source));
    EXPECT_FALSE(source == moved);
    EXPECT_FALSE(moved == source);
}

TEST(RhombusTest, CopyAndMove) {
    Rhombus<int> source({0, 0}, {2, 1}, {0, 2}, {-2, 1});
    Rhombus<int> copy;
    copy = source;
    EXPECT_TRUE(copy == source);
    EXPECT_NE(copy.getPoints(), source.getPoints());
    Rhombus<int>& alias = copy;
    copy = alias;
    EXPECT_TRUE(copy == source);

    Rhombus<int> moved(std::move(source));
    EXPECT_TRUE(moved == copy);
    EXPECT_EQ(source.getSize(), 0U);
    EXPECT_DOUBLE_EQ(source.getArea(), 0.0);
    EXPECT_EQ(source.getCenter(), (Point<double>{}));

    Rhombus<int> assigned;
    assigned = std::move(moved);
    EXPECT_TRUE(assigned == copy);
}

TEST(RhombusTest, Clone) {
    const Rhombus<int> rhombus({0, 0}, {2, 1}, {0, 2}, {-2, 1});
    const auto clone = rhombus.clone();
    EXPECT_NE(dynamic_cast<Rhombus<int>*>(clone.get()), nullptr);
    EXPECT_TRUE(*clone == rhombus);
}
