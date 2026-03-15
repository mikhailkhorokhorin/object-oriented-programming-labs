#include "rectangle.hpp"

#include <gtest/gtest.h>

TEST(RectangleTest, DefaultConstructor) {
    Rectangle rectangle;

    EXPECT_EQ(rectangle.getSize(), 4);

    const Point* points = rectangle.getPoints();
    Point expected{0, 0};

    for (size_t i = 0; i < 4; ++i)
        EXPECT_TRUE(points[i] == expected);
}

TEST(RectangleTest, ParameterizedConstructor) {
    Rectangle rectangle({0, 0}, {0, 2}, {3, 2}, {3, 0});

    EXPECT_EQ(rectangle.getSize(), 4);

    const Point* points = rectangle.getPoints();
    Point point1{0, 0};
    Point point2{0, 2};
    Point point3{3, 2};
    Point point4{3, 0};

    EXPECT_TRUE(points[0] == point1);
    EXPECT_TRUE(points[1] == point2);
    EXPECT_TRUE(points[2] == point3);
    EXPECT_TRUE(points[3] == point4);
}

TEST(RectangleTest, CopyConstructor) {
    Rectangle rectangle1({0, 0}, {0, 2}, {3, 2}, {3, 0});
    Rectangle rectangle2(rectangle1);

    EXPECT_TRUE(rectangle1 == rectangle2);
}

TEST(RectangleTest, MoveAssignment) {
    Rectangle rectangle1({0, 0}, {0, 2}, {3, 2}, {3, 0});
    Rectangle rectangle2;
    rectangle2 = std::move(rectangle1);

    EXPECT_EQ(rectangle2.getSize(), 4);

    const Point* points = rectangle2.getPoints();
    Point point1{0, 0};
    Point point2{0, 2};
    Point point3{3, 2};
    Point point4{3, 0};

    EXPECT_TRUE(points[0] == point1);
    EXPECT_TRUE(points[1] == point2);
    EXPECT_TRUE(points[2] == point3);
    EXPECT_TRUE(points[3] == point4);
}

TEST(RectangleTest, AreaCalculation) {
    Rectangle rectangle({0, 0}, {0, 2}, {3, 2}, {3, 0});

    EXPECT_DOUBLE_EQ(static_cast<double>(rectangle), 6.0);
}

TEST(RectangleTest, CenterCalculation) {
    Rectangle rectangle({0, 0}, {0, 2}, {4, 2}, {4, 0});
    Point center = rectangle.getCenter();

    EXPECT_DOUBLE_EQ(center.x, 2.0);
    EXPECT_DOUBLE_EQ(center.y, 1.0);
}

TEST(RectangleTest, InputOutput) {
    std::istringstream input("0 0 0 2 3 2 3 0");
    Rectangle rectangle;

    rectangle.read(input);
    std::ostringstream output;
    rectangle.print(output);

    EXPECT_EQ(output.str(), "(0,0) (0,2) (3,2) (3,0) ");
}

TEST(RectangleTest, EqualityOperator) {
    Rectangle rectangle1({0, 0}, {0, 2}, {3, 2}, {3, 0});
    Rectangle rectangle2({0, 0}, {0, 2}, {3, 2}, {3, 0});
    Rectangle rectangle3({0, 0}, {0, 3}, {3, 3}, {3, 0});

    EXPECT_TRUE(rectangle1 == rectangle2);
    EXPECT_FALSE(rectangle1 == rectangle3);
}

TEST(RectangleTest, Clone) {
    Rectangle rectangle1({0, 0}, {0, 2}, {3, 2}, {3, 0});
    auto rectangle2 = rectangle1.clone();

    EXPECT_TRUE(rectangle1 == *rectangle2);
}
