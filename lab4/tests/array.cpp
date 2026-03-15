#include "array.hpp"

#include <gtest/gtest.h>

#include "hexagon.hpp"
#include "pentagon.hpp"
#include "rhombus.hpp"

template <Scalar T>
shared_ptr<Rhombus<T>> makeRhombus() {
    return make_shared<Rhombus<T>>(Point<T>(0, 0), Point<T>(2, 0), Point<T>(2, 2), Point<T>(0, 2));
}

template <Scalar T>
shared_ptr<Pentagon<T>> makePentagon() {
    return make_shared<Pentagon<T>>(Point<T>(0, 0), Point<T>(1, 2), Point<T>(2, 3), Point<T>(3, 2),
                                    Point<T>(2, 0));
}

template <Scalar T>
shared_ptr<Hexagon<T>> makeHexagon() {
    return make_shared<Hexagon<T>>(Point<T>(0, 0), Point<T>(1, 0), Point<T>(2, 1), Point<T>(2, 2),
                                   Point<T>(1, 3), Point<T>(0, 2));
}

TEST(ArrayTest, AddAndGetFigures) {
    Array<int> array;
    auto rhombus = makeRhombus<int>();
    auto pentagon = makePentagon<int>();
    auto hexagon = makeHexagon<int>();

    array.addFigure(rhombus);
    array.addFigure(pentagon);
    array.addFigure(hexagon);

    EXPECT_EQ(array.getSize(), 3);
    EXPECT_EQ(array.getFigure(0), rhombus);
    EXPECT_EQ(array.getFigure(1), pentagon);
    EXPECT_EQ(array.getFigure(2), hexagon);

    EXPECT_EQ(array[0], rhombus);
    EXPECT_EQ(array[1], pentagon);
    EXPECT_EQ(array[2], hexagon);
}

TEST(ArrayTest, TotalArea) {
    Array<int> array;
    auto rhombus = makeRhombus<int>();
    auto pentagon = makePentagon<int>();
    auto hexagon = makeHexagon<int>();

    array.addFigure(rhombus);
    array.addFigure(pentagon);
    array.addFigure(hexagon);

    double expected_area = static_cast<double>(*rhombus) + static_cast<double>(*pentagon) +
                           static_cast<double>(*hexagon);
    EXPECT_DOUBLE_EQ(array.getAllArea(), expected_area);
}

TEST(ArrayTest, RemoveFigure) {
    Array<int> array;
    auto rhombus = makeRhombus<int>();
    auto pentagon = makePentagon<int>();
    auto hexagon = makeHexagon<int>();

    array.addFigure(rhombus);
    array.addFigure(pentagon);
    array.addFigure(hexagon);

    array.removeFigure(1);
    EXPECT_EQ(array.getSize(), 2);
    EXPECT_EQ(array.getFigure(0), rhombus);
    EXPECT_EQ(array.getFigure(1), hexagon);

    array.removeFigure(0);
    EXPECT_EQ(array.getSize(), 1);
    EXPECT_EQ(array.getFigure(0), hexagon);

    array.removeFigure(0);
    EXPECT_EQ(array.getSize(), 0);

    array.removeFigure(0);
    EXPECT_EQ(array.getSize(), 0);
}

TEST(ArrayTest, CopyArray) {
    Array<int> array1;
    auto rhombus = makeRhombus<int>();
    array1.addFigure(rhombus);

    Array<int> array2 = array1;
    EXPECT_EQ(array2.getSize(), array1.getSize());
    EXPECT_NE(array2.getFigure(0), array1.getFigure(0));
    EXPECT_EQ(static_cast<double>(*array2.getFigure(0)), static_cast<double>(*array1.getFigure(0)));
}

TEST(ArrayTest, MoveArray) {
    Array<int> array1;
    auto rhombus = makeRhombus<int>();
    array1.addFigure(rhombus);

    Array<int> array2 = std::move(array1);
    EXPECT_EQ(array2.getSize(), 1);
    EXPECT_EQ(array1.getSize(), 0);
}

TEST(ArrayTest, ResizeArray) {
    Array<int> array(2);
    auto rhombus = makeRhombus<int>();
    auto pentagon = makePentagon<int>();
    auto hexagon = makeHexagon<int>();

    array.addFigure(rhombus);
    array.addFigure(pentagon);
    EXPECT_EQ(array.getCapacity(), 2);

    array.addFigure(hexagon);
    EXPECT_GE(array.getCapacity(), 3);
    EXPECT_EQ(array.getSize(), 3);
}

TEST(ArrayTest, IndexOutOfBounds) {
    Array<int> array;
    auto rhombus = makeRhombus<int>();
    array.addFigure(rhombus);

    EXPECT_EQ(array.getFigure(10), nullptr);
    EXPECT_EQ(array[10], nullptr);
}

TEST(ArrayTest, PrintFigures) {
    Array<int> array;
    auto rhombus = makeRhombus<int>();
    array.addFigure(rhombus);

    EXPECT_NO_THROW(array.printFigures());
}
