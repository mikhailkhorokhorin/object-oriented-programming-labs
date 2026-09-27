#include "rectangle.hpp"

#include <gtest/gtest.h>

#include <sstream>
#include <utility>

TEST(RectangleTest, AreaAndCenter) {
    const Rectangle rectangle({0, 0}, {3, 0}, {3, 2}, {0, 2});
    EXPECT_DOUBLE_EQ(static_cast<double>(rectangle), 6);
    EXPECT_EQ(rectangle.getCenter(), (Point{1.5, 1}));
}

TEST(RectangleTest, ReadReplacesPoints) {
    Rectangle rectangle;
    std::istringstream in("0 0 4 0 4 1 0 1");
    rectangle.read(in);
    EXPECT_DOUBLE_EQ(static_cast<double>(rectangle), 4);
    EXPECT_EQ(rectangle.getPoints()[2], (Point{4, 1}));
}

TEST(RectangleTest, CopyAndMove) {
    const Rectangle original({0, 0}, {3, 0}, {3, 2}, {0, 2});
    Rectangle copy(original);
    EXPECT_TRUE(copy == original);
    Rectangle moved(std::move(copy));
    EXPECT_TRUE(moved == original);
    Rectangle assigned;
    assigned = original;
    EXPECT_TRUE(assigned == original);
}

TEST(RectangleTest, Clone) {
    const Rectangle rectangle({0, 0}, {3, 0}, {3, 2}, {0, 2});
    const auto clone = rectangle.clone();
    EXPECT_NE(dynamic_cast<Rectangle*>(clone.get()), nullptr);
    EXPECT_DOUBLE_EQ(static_cast<double>(*clone), 6);
}
