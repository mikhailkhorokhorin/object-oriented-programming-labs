#include "pentagon.hpp"

#include <gtest/gtest.h>

TEST(PentagonTest, DefaultConstructor) {
    Pentagon<int> pentagon;
    EXPECT_EQ(pentagon.getSize(), 0);
}

TEST(PentagonTest, ParameterConstructor) {
    Point<int> point1{0, 0}, point2{1, 0}, point3{1, 1}, point4{0, 1}, point5{0, 2};
    Pentagon<int> pentagon(point1, point2, point3, point4, point5);

    EXPECT_EQ(pentagon.getSize(), 5);

    const Point<int>* points = pentagon.getPoints();
    EXPECT_EQ(points[0], point1);
    EXPECT_EQ(points[1], point2);
    EXPECT_EQ(points[2], point3);
    EXPECT_EQ(points[3], point4);
    EXPECT_EQ(points[4], point5);
}

TEST(PentagonTest, CopyConstructor) {
    Point<int> point1{0, 0}, point2{1, 0}, point3{1, 1}, point4{0, 1}, point5{0, 2};
    Pentagon<int> pentagon1(point1, point2, point3, point4, point5);
    Pentagon<int> pentagon2(pentagon1);

    EXPECT_EQ(pentagon1.getSize(), pentagon2.getSize());
    EXPECT_TRUE(pentagon1 == pentagon2);
}

TEST(PentagonTest, GetCenter) {
    Pentagon<double> pentagon(Point<double>(0, 0), Point<double>(2, 0), Point<double>(2, 2),
                              Point<double>(0, 2), Point<double>(1, 3));
    Point<double> center = pentagon.getCenter();
    EXPECT_DOUBLE_EQ(center.x, (0 + 2 + 2 + 0 + 1) / 5.0);
    EXPECT_DOUBLE_EQ(center.y, (0 + 0 + 2 + 2 + 3) / 5.0);
}

TEST(PentagonTest, GetArea) {
    Pentagon<int> pentagon(Point<int>(0, 0), Point<int>(4, 0), Point<int>(5, 3), Point<int>(2, 5),
                           Point<int>(-1, 3));
    double area = pentagon.getArea();

    EXPECT_DOUBLE_EQ(area, 21.0);
}

TEST(PentagonTest, Print) {
    Pentagon<int> pentagon(Point<int>(0, 0), Point<int>(1, 0), Point<int>(1, 1), Point<int>(0, 1),
                           Point<int>(0, 2));
    ostringstream os;

    pentagon.print(os);
    string output = os.str();

    EXPECT_NE(output.find("Area"), string::npos);
    EXPECT_NE(output.find("(0,0)"), string::npos);
}

TEST(PentagonTest, Read) {
    Pentagon<int> pentagon;

    istringstream is("0 0 1 0 1 1 0 1 0 2");
    pentagon.read(is);

    Point<int> point1{0, 0}, point2{1, 0}, point3{1, 1}, point4{0, 1}, point5{0, 2};
    const Point<int>* points = pentagon.getPoints();
    EXPECT_EQ(points[0], point1);
    EXPECT_EQ(points[1], point2);
    EXPECT_EQ(points[2], point3);
    EXPECT_EQ(points[3], point4);
    EXPECT_EQ(points[4], point5);
}

TEST(PentagonTest, OperatorEquals) {
    Pentagon<int> pentagon1(Point<int>(0, 0), Point<int>(1, 0), Point<int>(1, 1), Point<int>(0, 1),
                            Point<int>(0, 2));
    Pentagon<int> pentagon2(pentagon1);
    Pentagon<int> pentagon3(Point<int>(1, 1), Point<int>(2, 1), Point<int>(2, 2), Point<int>(1, 2),
                            Point<int>(0, 2));

    EXPECT_TRUE(pentagon1 == pentagon2);
    EXPECT_FALSE(pentagon1 == pentagon3);
}

TEST(PentagonTest, Clone) {
    Pentagon<int> pentagon1(Point<int>(0, 0), Point<int>(1, 0), Point<int>(1, 1), Point<int>(0, 1),
                            Point<int>(0, 2));
    auto pentagon2 = pentagon1.clone();
    EXPECT_TRUE(dynamic_cast<Pentagon<int>*>(pentagon2.get()) != nullptr);
    EXPECT_TRUE(pentagon1 == *pentagon2);
}
