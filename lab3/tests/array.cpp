#include "array.hpp"

#include <gtest/gtest.h>

#include <memory>
#include <sstream>
#include <utility>

#include "rectangle.hpp"
#include "square.hpp"
#include "trapezoid.hpp"

namespace {

Array makeArray() {
    Array array;
    array.addFigure(std::make_unique<Square>(Point{0, 0}, Point{0, 2}, Point{2, 2}, Point{2, 0}));
    array.addFigure(
        std::make_unique<Rectangle>(Point{0, 0}, Point{0, 3}, Point{3, 3}, Point{3, 0}));
    array.addFigure(
        std::make_unique<Trapezoid>(Point{0, 0}, Point{2, 0}, Point{3, 2}, Point{1, 2}));
    return array;
}

}

TEST(ArrayTest, StoresFiguresPolymorphically) {
    const Array array = makeArray();
    EXPECT_EQ(array.getSize(), 3U);
    EXPECT_NE(dynamic_cast<Square*>(array.getFigure(0)), nullptr);
    EXPECT_NE(dynamic_cast<Rectangle*>(array.getFigure(1)), nullptr);
    EXPECT_NE(dynamic_cast<Trapezoid*>(array[2]), nullptr);
    EXPECT_EQ(array[3], nullptr);
    EXPECT_EQ(array.getFigure(3), nullptr);
}

TEST(ArrayTest, TotalArea) {
    EXPECT_DOUBLE_EQ(makeArray().getAllArea(), 4 + 9 + 4);
    EXPECT_DOUBLE_EQ(Array().getAllArea(), 0);
}

TEST(ArrayTest, IgnoresNullFigure) {
    Array array;
    array.addFigure(nullptr);
    EXPECT_EQ(array.getSize(), 0U);
}

TEST(ArrayTest, ZeroCapacityGrowsOnAdd) {
    Array array(0);
    EXPECT_EQ(array.getCapacity(), 0U);
    array.addFigure(std::make_unique<Square>());
    array.addFigure(std::make_unique<Square>());
    EXPECT_EQ(array.getSize(), 2U);
    EXPECT_GE(array.getCapacity(), 2U);
}

TEST(ArrayTest, GrowsByDoubling) {
    Array array(2);
    array.addFigure(std::make_unique<Square>());
    array.addFigure(std::make_unique<Square>());
    EXPECT_EQ(array.getCapacity(), 2U);
    array.addFigure(std::make_unique<Square>());
    EXPECT_EQ(array.getCapacity(), 4U);
    EXPECT_EQ(array.getSize(), 3U);
}

TEST(ArrayTest, RemoveShiftsFigures) {
    Array array = makeArray();
    array.removeFigure(1);
    EXPECT_EQ(array.getSize(), 2U);
    EXPECT_NE(dynamic_cast<Square*>(array[0]), nullptr);
    EXPECT_NE(dynamic_cast<Trapezoid*>(array[1]), nullptr);
    EXPECT_EQ(array[2], nullptr);
    array.removeFigure(5);
    EXPECT_EQ(array.getSize(), 2U);
    array.removeFigure(0);
    array.removeFigure(0);
    EXPECT_EQ(array.getSize(), 0U);
}

TEST(ArrayTest, CopyIsDeep) {
    const Array original = makeArray();
    Array copy(original);
    EXPECT_EQ(copy.getSize(), 3U);
    EXPECT_NE(copy[0], original[0]);
    EXPECT_TRUE(*copy[0] == *original[0]);
    copy.removeFigure(0);
    EXPECT_EQ(original.getSize(), 3U);

    Array assigned;
    assigned = original;
    EXPECT_DOUBLE_EQ(assigned.getAllArea(), original.getAllArea());
    const Array& alias = assigned;
    assigned = alias;
    EXPECT_EQ(assigned.getSize(), 3U);
}

TEST(ArrayTest, MoveTransfersFigures) {
    Array source = makeArray();
    Figure* first = source[0];
    Array moved(std::move(source));
    EXPECT_EQ(moved.getSize(), 3U);
    EXPECT_EQ(moved[0], first);

    Array assigned;
    assigned = std::move(moved);
    EXPECT_EQ(assigned.getSize(), 3U);
    EXPECT_EQ(assigned[0], first);
}

TEST(ArrayTest, PrintFigures) {
    Array array;
    array.addFigure(std::make_unique<Square>(Point{0, 0}, Point{2, 0}, Point{2, 2}, Point{0, 2}));
    std::ostringstream out;
    array.printFigures(out);
    EXPECT_EQ(out.str(), "Figure 1: (0, 0) (2, 0) (2, 2) (0, 2) Center: (1, 1) Area: 4\n");
}
