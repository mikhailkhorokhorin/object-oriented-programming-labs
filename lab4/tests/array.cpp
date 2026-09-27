#include "array.hpp"

#include <gtest/gtest.h>

#include <memory>
#include <sstream>
#include <utility>

#include "hexagon.hpp"
#include "pentagon.hpp"
#include "rhombus.hpp"

namespace {

std::shared_ptr<Rhombus<int>> makeRhombus() {
    return std::make_shared<Rhombus<int>>(Point<int>{0, 0}, Point<int>{2, 1}, Point<int>{0, 2},
                                          Point<int>{-2, 1});
}

std::shared_ptr<Pentagon<int>> makePentagon() {
    return std::make_shared<Pentagon<int>>(Point<int>{0, 0}, Point<int>{2, 0}, Point<int>{3, 2},
                                           Point<int>{1, 4}, Point<int>{-1, 2});
}

std::shared_ptr<Hexagon<int>> makeHexagon() {
    return std::make_shared<Hexagon<int>>(Point<int>{0, 0}, Point<int>{2, 0}, Point<int>{3, 1},
                                          Point<int>{2, 2}, Point<int>{0, 2}, Point<int>{-1, 1});
}

Array<int> makeArray() {
    Array<int> array;
    array.addFigure(makeRhombus());
    array.addFigure(makePentagon());
    array.addFigure(makeHexagon());
    return array;
}

}

TEST(ArrayTest, AddAndGet) {
    Array<int> array;
    const auto rhombus = makeRhombus();
    array.addFigure(rhombus);
    array.addFigure(nullptr);
    EXPECT_EQ(array.getSize(), 1U);
    EXPECT_EQ(array.getFigure(0), rhombus);
    EXPECT_EQ(array[0], rhombus);
    EXPECT_EQ(array[1], nullptr);
    EXPECT_EQ(array.getFigure(10), nullptr);
}

TEST(ArrayTest, TotalArea) {
    EXPECT_DOUBLE_EQ(makeArray().getAllArea(), 4.0 + 10.0 + 6.0);
}

TEST(ArrayTest, ZeroCapacityGrowsOnAdd) {
    Array<int> array(0);
    array.addFigure(makeRhombus());
    array.addFigure(makeHexagon());
    EXPECT_EQ(array.getSize(), 2U);
    EXPECT_GE(array.getCapacity(), 2U);
}

TEST(ArrayTest, GrowsByDoubling) {
    Array<int> array(2);
    array.addFigure(makeRhombus());
    array.addFigure(makeRhombus());
    EXPECT_EQ(array.getCapacity(), 2U);
    array.addFigure(makeRhombus());
    EXPECT_EQ(array.getCapacity(), 4U);
}

TEST(ArrayTest, RemoveShiftsFigures) {
    Array<int> array;
    const auto rhombus = makeRhombus();
    const auto pentagon = makePentagon();
    const auto hexagon = makeHexagon();
    array.addFigure(rhombus);
    array.addFigure(pentagon);
    array.addFigure(hexagon);
    array.removeFigure(1);
    EXPECT_EQ(array.getSize(), 2U);
    EXPECT_EQ(array[0], rhombus);
    EXPECT_EQ(array[1], hexagon);
    array.removeFigure(7);
    EXPECT_EQ(array.getSize(), 2U);
}

TEST(ArrayTest, RemoveReleasesOwnership) {
    Array<int> array;
    const auto rhombus = makeRhombus();
    const auto hexagon = makeHexagon();
    array.addFigure(rhombus);
    array.addFigure(hexagon);
    EXPECT_EQ(hexagon.use_count(), 2);
    array.removeFigure(0);
    EXPECT_EQ(rhombus.use_count(), 1);
    EXPECT_EQ(hexagon.use_count(), 2);
    array.removeFigure(0);
    EXPECT_EQ(hexagon.use_count(), 1);
    EXPECT_EQ(array.getSize(), 0U);
}

TEST(ArrayTest, CopyIsDeep) {
    const Array<int> original = makeArray();
    Array<int> copy(original);
    EXPECT_EQ(copy.getSize(), 3U);
    EXPECT_NE(copy[0], original[0]);
    EXPECT_TRUE(*copy[0] == *original[0]);
    copy.removeFigure(0);
    EXPECT_EQ(original.getSize(), 3U);

    Array<int> assigned;
    assigned = original;
    EXPECT_DOUBLE_EQ(assigned.getAllArea(), original.getAllArea());
    EXPECT_NE(assigned[2], original[2]);
}

TEST(ArrayTest, MoveTransfersFigures) {
    Array<int> source = makeArray();
    const auto first = source[0];
    Array<int> moved(std::move(source));
    EXPECT_EQ(moved.getSize(), 3U);
    EXPECT_EQ(moved[0], first);

    Array<int> assigned;
    assigned = std::move(moved);
    EXPECT_EQ(assigned.getSize(), 3U);
    EXPECT_EQ(assigned[0], first);
}

TEST(ArrayTest, PrintFigures) {
    Array<int> array;
    array.addFigure(makeRhombus());
    std::ostringstream out;
    array.printFigures(out);
    EXPECT_EQ(out.str(), "Figure 1: (0, 0) (2, 1) (0, 2) (-2, 1) Center: (0, 1) Area: 4\n");
}
