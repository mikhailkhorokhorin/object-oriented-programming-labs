#include "square.hpp"

#include <gtest/gtest.h>

TEST(SquareTest, DefaultConstructor) {
    Square square;

    EXPECT_EQ(square.getSize(), 4);

    const Point* points = square.getPoints();
    Point expected{0, 0};

    for (size_t i = 0; i < 4; ++i)
        EXPECT_TRUE(points[i] == expected);
}

TEST(SquareTest, ParameterizedConstructor) {
    Square square({0, 0}, {0, 1}, {1, 1}, {1, 0});

    EXPECT_EQ(square.getSize(), 4);

    const Point* points = square.getPoints();
    Point point1{0, 0};
    Point point2{0, 1};
    Point point3{1, 1};
    Point point4{1, 0};

    EXPECT_TRUE(points[0] == point1);
    EXPECT_TRUE(points[1] == point2);
    EXPECT_TRUE(points[2] == point3);
    EXPECT_TRUE(points[3] == point4);
}

TEST(SquareTest, CopyConstructor) {
    Square square1({0, 0}, {0, 1}, {1, 1}, {1, 0});
    Square square2(square1);

    EXPECT_TRUE(square1 == square2);
}

TEST(SquareTest, MoveAssignment) {
    Square square1({0, 0}, {0, 1}, {1, 1}, {1, 0});
    Square square2;
    square2 = std::move(square1);

    EXPECT_EQ(square2.getSize(), 4);

    const Point* points = square2.getPoints();
    Point point1{0, 0};
    Point point2{0, 1};
    Point point3{1, 1};
    Point point4{1, 0};

    EXPECT_TRUE(points[0] == point1);
    EXPECT_TRUE(points[1] == point2);
    EXPECT_TRUE(points[2] == point3);
    EXPECT_TRUE(points[3] == point4);
}

TEST(SquareTest, AreaCalculation) {
    Square square({0, 0}, {0, 2}, {2, 2}, {2, 0});

    EXPECT_DOUBLE_EQ(static_cast<double>(square), 4.0);
}

TEST(SquareTest, CenterCalculation) {
    Square square({0, 0}, {0, 2}, {2, 2}, {2, 0});
    Point center = square.getCenter();

    EXPECT_DOUBLE_EQ(center.x, 1.0);
    EXPECT_DOUBLE_EQ(center.y, 1.0);
}

TEST(SquareTest, InputOutput) {
    std::istringstream input("0 0 0 1 1 1 1 0");
    Square square;

    square.read(input);
    std::ostringstream output;
    square.print(output);

    EXPECT_EQ(output.str(), "(0,0) (0,1) (1,1) (1,0) ");
}

TEST(SquareTest, EqualityOperator) {
    Square square1({0, 0}, {0, 1}, {1, 1}, {1, 0});
    Square square2({0, 0}, {0, 1}, {1, 1}, {1, 0});
    Square square3({0, 0}, {0, 2}, {2, 2}, {2, 0});

    EXPECT_TRUE(square1 == square2);
    EXPECT_FALSE(square1 == square3);
}

TEST(SquareTest, Clone) {
    Square square1({0, 0}, {0, 1}, {1, 1}, {1, 0});
    auto square2 = square1.clone();

    EXPECT_TRUE(square1 == *square2);
}
