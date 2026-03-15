#include "hexagon.hpp"

#include <gtest/gtest.h>

TEST(HexagonTest, DefaultConstructor) {
    Hexagon<int> hexagon;
    EXPECT_EQ(hexagon.getSize(), 0);
}

TEST(HexagonTest, ParameterConstructor) {
    Point<int> point1{0, 0}, point2{2, 0}, point3{3, 2}, point4{2, 4}, point5{0, 4}, point6{-1, 2};
    Hexagon<int> hexagon(point1, point2, point3, point4, point5, point6);

    EXPECT_EQ(hexagon.getSize(), 6);

    const Point<int>* points = hexagon.getPoints();
    EXPECT_EQ(points[0], point1);
    EXPECT_EQ(points[1], point2);
    EXPECT_EQ(points[2], point3);
    EXPECT_EQ(points[3], point4);
    EXPECT_EQ(points[4], point5);
    EXPECT_EQ(points[5], point6);
}

TEST(HexagonTest, CopyConstructor) {
    Point<int> point1{0, 0}, point2{2, 0}, point3{3, 2}, point4{2, 4}, point5{0, 4}, point6{-1, 2};
    Hexagon<int> hexagon1(point1, point2, point3, point4, point5, point6);
    Hexagon<int> hexagon2(hexagon1);

    EXPECT_EQ(hexagon1.getSize(), hexagon2.getSize());
    EXPECT_TRUE(hexagon1 == hexagon2);
}

TEST(HexagonTest, GetCenter) {
    Hexagon<double> hexagon(Point<double>(0, 0), Point<double>(2, 0), Point<double>(3, 2),
                            Point<double>(2, 4), Point<double>(0, 4), Point<double>(-1, 2));
    Point<double> center = hexagon.getCenter();

    EXPECT_DOUBLE_EQ(center.x, (0 + 2 + 3 + 2 + 0 + (-1)) / 6.0);
    EXPECT_DOUBLE_EQ(center.y, (0 + 0 + 2 + 4 + 4 + 2) / 6.0);
}

TEST(HexagonTest, GetArea) {
    Hexagon<int> hexagon(Point<int>(0, 0), Point<int>(2, 0), Point<int>(3, 2), Point<int>(2, 4),
                         Point<int>(0, 4), Point<int>(-1, 2));

    double area = hexagon.getArea();
    EXPECT_NEAR(area, 12.0, 1e-6);
}

TEST(HexagonTest, Print) {
    Hexagon<int> hexagon(Point<int>(0, 0), Point<int>(1, 0), Point<int>(2, 1), Point<int>(1, 2),
                         Point<int>(0, 2), Point<int>(-1, 1));
    ostringstream os;

    hexagon.print(os);
    string output = os.str();

    EXPECT_NE(output.find("Area"), string::npos);
    EXPECT_NE(output.find("(0,0)"), string::npos);
}

TEST(HexagonTest, Read) {
    Hexagon<int> hexagon;

    istringstream is("0 0 2 0 3 2 2 4 0 4 -1 2");
    hexagon.read(is);

    Point<int> point1{0, 0}, point2{2, 0}, point3{3, 2}, point4{2, 4}, point5{0, 4}, point6{-1, 2};
    const Point<int>* points = hexagon.getPoints();
    EXPECT_EQ(points[0], point1);
    EXPECT_EQ(points[1], point2);
    EXPECT_EQ(points[2], point3);
    EXPECT_EQ(points[3], point4);
    EXPECT_EQ(points[4], point5);
    EXPECT_EQ(points[5], point6);
}

TEST(HexagonTest, OperatorEquals) {
    Hexagon<int> hexagon1(Point<int>(0, 0), Point<int>(2, 0), Point<int>(3, 2), Point<int>(2, 4),
                          Point<int>(0, 4), Point<int>(-1, 2));
    Hexagon<int> hexagon2(hexagon1);
    Hexagon<int> hexagon3(Point<int>(1, 1), Point<int>(2, 1), Point<int>(3, 3), Point<int>(2, 5),
                          Point<int>(0, 5), Point<int>(-1, 3));

    EXPECT_TRUE(hexagon1 == hexagon2);
    EXPECT_FALSE(hexagon1 == hexagon3);
}

TEST(HexagonTest, Clone) {
    Hexagon<int> hexagon1(Point<int>(0, 0), Point<int>(2, 0), Point<int>(3, 2), Point<int>(2, 4),
                          Point<int>(0, 4), Point<int>(-1, 2));

    auto hexagon2 = hexagon1.clone();
    EXPECT_TRUE(dynamic_cast<Hexagon<int>*>(hexagon2.get()) != nullptr);
    EXPECT_TRUE(hexagon1 == *hexagon2);
}
