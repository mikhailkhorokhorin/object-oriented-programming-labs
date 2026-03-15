#include "rhombus.hpp"

#include <gtest/gtest.h>

TEST(RhombusTest, DefaultConstructor) {
    Rhombus<int> rhombus;
    EXPECT_EQ(rhombus.getSize(), 0);
}

TEST(RhombusTest, ParameterConstructor) {
    Point<int> point1{0, 0}, point2{2, 0}, point3{2, 2}, point4{0, 2};
    Rhombus<int> rhombus(point1, point2, point3, point4);

    EXPECT_EQ(rhombus.getSize(), 4);

    const Point<int>* points = rhombus.getPoints();
    EXPECT_EQ(points[0], point1);
    EXPECT_EQ(points[1], point2);
    EXPECT_EQ(points[2], point3);
    EXPECT_EQ(points[3], point4);
}

TEST(RhombusTest, CopyConstructor) {
    Point<int> point1{0, 0}, point2{2, 0}, point3{2, 2}, point4{0, 2};
    Rhombus<int> rhombus1(point1, point2, point3, point4);
    Rhombus<int> rhombus2(rhombus1);

    EXPECT_EQ(rhombus1.getSize(), rhombus2.getSize());
    EXPECT_TRUE(rhombus1 == rhombus2);
}

TEST(RhombusTest, GetCenter) {
    Rhombus<double> rhombus(Point<double>(0, 0), Point<double>(2, 0), Point<double>(2, 2),
                            Point<double>(0, 2));
    Point<double> center = rhombus.getCenter();

    EXPECT_DOUBLE_EQ(center.x, 1.0);
    EXPECT_DOUBLE_EQ(center.y, 1.0);
}

TEST(RhombusTest, GetArea) {
    Rhombus<double> rhombus(Point<double>(0, 0), Point<double>(2, 0), Point<double>(2, 2),
                            Point<double>(0, 2));

    double expected_area = 4.0;
    double d1 = sqrt(pow(0 - 2, 2) + pow(0 - 2, 2));
    double d2 = sqrt(pow(2 - 0, 2) + pow(0 - 2, 2));
    expected_area = d1 * d2 / 2.0;

    EXPECT_DOUBLE_EQ(rhombus.getArea(), expected_area);
}

TEST(RhombusTest, Print) {
    Rhombus<int> rhombus(Point<int>(0, 0), Point<int>(2, 0), Point<int>(2, 2), Point<int>(0, 2));
    ostringstream os;

    rhombus.print(os);
    string output = os.str();

    EXPECT_NE(output.find("Area"), string::npos);
    EXPECT_NE(output.find("(0,0)"), string::npos);
}

TEST(RhombusTest, Read) {
    Rhombus<int> rhombus;

    istringstream is("0 0 2 0 2 2 0 2");
    rhombus.read(is);

    Point<int> point1{0, 0}, point2{2, 0}, point3{2, 2}, point4{0, 2};
    const Point<int>* points = rhombus.getPoints();
    EXPECT_EQ(points[0], point1);
    EXPECT_EQ(points[1], point2);
    EXPECT_EQ(points[2], point3);
    EXPECT_EQ(points[3], point4);
}

TEST(RhombusTest, OperatorEquals) {
    Rhombus<int> rhombus1(Point<int>(0, 0), Point<int>(2, 0), Point<int>(2, 2), Point<int>(0, 2));
    Rhombus<int> rhombus2(rhombus1);
    Rhombus<int> rhombus3(Point<int>(1, 1), Point<int>(3, 1), Point<int>(3, 3), Point<int>(1, 3));

    EXPECT_TRUE(rhombus1 == rhombus2);
    EXPECT_FALSE(rhombus1 == rhombus3);
}

TEST(RhombusTest, Clone) {
    Rhombus<int> rhombus1(Point<int>(0, 0), Point<int>(2, 0), Point<int>(2, 2), Point<int>(0, 2));
    auto rhombus2 = rhombus1.clone();
    EXPECT_TRUE(dynamic_cast<Rhombus<int>*>(rhombus2.get()) != nullptr);
    EXPECT_TRUE(rhombus1 == *rhombus2);
}
