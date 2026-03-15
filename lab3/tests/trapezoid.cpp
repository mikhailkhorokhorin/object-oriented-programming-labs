#include "trapezoid.hpp"

#include <gtest/gtest.h>

TEST(TrapezoidTest, DefaultConstructor) {
    Trapezoid trapezoid;

    EXPECT_EQ(trapezoid.getSize(), 4);

    const Point* points = trapezoid.getPoints();
    Point expected{0, 0};

    for (size_t i = 0; i < 4; ++i)
        EXPECT_TRUE(points[i] == expected);
}

TEST(TrapezoidTest, ParameterizedConstructor) {
    Trapezoid trapezoid({0, 0}, {2, 0}, {3, 2}, {1, 2});

    EXPECT_EQ(trapezoid.getSize(), 4);

    const Point* points = trapezoid.getPoints();
    Point point1{0, 0};
    Point point2{2, 0};
    Point point3{3, 2};
    Point point4{1, 2};

    EXPECT_TRUE(points[0] == point1);
    EXPECT_TRUE(points[1] == point2);
    EXPECT_TRUE(points[2] == point3);
    EXPECT_TRUE(points[3] == point4);
}

TEST(TrapezoidTest, CopyConstructor) {
    Trapezoid trapezoid1({0, 0}, {2, 0}, {3, 2}, {1, 2});
    Trapezoid trapezoid2(trapezoid1);

    EXPECT_TRUE(trapezoid1 == trapezoid2);
}

TEST(TrapezoidTest, MoveAssignment) {
    Trapezoid trapezoid1({0, 0}, {2, 0}, {3, 2}, {1, 2});
    Trapezoid trapezoid2;
    trapezoid2 = std::move(trapezoid1);

    EXPECT_EQ(trapezoid2.getSize(), 4);

    const Point* points = trapezoid2.getPoints();
    Point point1{0, 0};
    Point point2{2, 0};
    Point point3{3, 2};
    Point point4{1, 2};

    EXPECT_TRUE(points[0] == point1);
    EXPECT_TRUE(points[1] == point2);
    EXPECT_TRUE(points[2] == point3);
    EXPECT_TRUE(points[3] == point4);
}

TEST(TrapezoidTest, AreaCalculation) {
    Trapezoid trapezoid({0, 0}, {2, 0}, {3, 2}, {1, 2});

    EXPECT_DOUBLE_EQ(static_cast<double>(trapezoid), 4.0);
}

TEST(TrapezoidTest, CenterCalculation) {
    Trapezoid trapezoid({0, 0}, {2, 0}, {3, 2}, {1, 2});
    Point center = trapezoid.getCenter();

    EXPECT_DOUBLE_EQ(center.x, 1.5);
    EXPECT_DOUBLE_EQ(center.y, 1.0);
}

TEST(TrapezoidTest, InputOutput) {
    std::istringstream input("0 0 2 0 3 2 1 2");
    Trapezoid trapezoid;

    trapezoid.read(input);
    std::ostringstream output;
    trapezoid.print(output);

    EXPECT_EQ(output.str(), "(0,0) (2,0) (3,2) (1,2) ");
}

TEST(TrapezoidTest, EqualityOperator) {
    Trapezoid trapezoid1({0, 0}, {2, 0}, {3, 2}, {1, 2});
    Trapezoid trapezoid2({0, 0}, {2, 0}, {3, 2}, {1, 2});
    Trapezoid trapezoid3({0, 0}, {2, 0}, {4, 2}, {1, 2});

    EXPECT_TRUE(trapezoid1 == trapezoid2);
    EXPECT_FALSE(trapezoid1 == trapezoid3);
}

TEST(TrapezoidTest, Clone) {
    Trapezoid trapezoid1({0, 0}, {2, 0}, {3, 2}, {1, 2});
    auto trapezoid2 = trapezoid1.clone();

    EXPECT_TRUE(trapezoid1 == *trapezoid2);
}
