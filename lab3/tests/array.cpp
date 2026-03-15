#include "array.hpp"

#include <gtest/gtest.h>

#include "rectangle.hpp"
#include "square.hpp"
#include "trapezoid.hpp"

TEST(ArrayTest, AddVariousFigures) {
    Array array;

    Square* square = new Square({0, 0}, {0, 1}, {1, 1}, {1, 0});
    Rectangle* rectangle = new Rectangle({0, 0}, {0, 2}, {3, 2}, {3, 0});
    Trapezoid* trapezoid = new Trapezoid({0, 0}, {2, 0}, {3, 2}, {1, 2});

    array.addFigure(square);
    array.addFigure(rectangle);
    array.addFigure(trapezoid);

    EXPECT_EQ(array.getSize(), 3);
    EXPECT_DOUBLE_EQ(array.getAllArea(), static_cast<double>(*square) +
                                             static_cast<double>(*rectangle) +
                                             static_cast<double>(*trapezoid));

    EXPECT_TRUE(dynamic_cast<Square*>(array.getFigure(0)) != nullptr);
    EXPECT_TRUE(dynamic_cast<Rectangle*>(array.getFigure(1)) != nullptr);
    EXPECT_TRUE(dynamic_cast<Trapezoid*>(array.getFigure(2)) != nullptr);
}

TEST(ArrayTest, CopyAndMoveWithVariousFigures) {
    Array array1;
    array1.addFigure(new Square({0, 0}, {0, 1}, {1, 1}, {1, 0}));
    array1.addFigure(new Rectangle({0, 0}, {0, 2}, {3, 2}, {3, 0}));
    array1.addFigure(new Trapezoid({0, 0}, {2, 0}, {3, 2}, {1, 2}));

    Array array2(array1);

    EXPECT_EQ(array2.getSize(), 3);
    EXPECT_DOUBLE_EQ(array2.getAllArea(), array1.getAllArea());

    Array array3(std::move(array1));

    EXPECT_EQ(array3.getSize(), 3);
    EXPECT_EQ(array1.getSize(), 0);

    Array array4;
    array4 = array2;

    EXPECT_EQ(array4.getSize(), 3);
    EXPECT_DOUBLE_EQ(array4.getAllArea(), array2.getAllArea());
}

TEST(ArrayTest, RemoveFiguresPolymorphic) {
    Array array;
    array.addFigure(new Square({0, 0}, {0, 1}, {1, 1}, {1, 0}));
    array.addFigure(new Rectangle({0, 0}, {0, 2}, {3, 2}, {3, 0}));
    array.addFigure(new Trapezoid({0, 0}, {2, 0}, {3, 2}, {1, 2}));

    array.removeFigure(1);

    EXPECT_EQ(array.getSize(), 2);
    EXPECT_TRUE(dynamic_cast<Square*>(array.getFigure(0)) != nullptr);
    EXPECT_TRUE(dynamic_cast<Trapezoid*>(array.getFigure(1)) != nullptr);
}

TEST(ArrayTest, OperatorIndexPolymorphic) {
    Array array;
    array.addFigure(new Square({0, 0}, {0, 1}, {1, 1}, {1, 0}));
    array.addFigure(new Rectangle({0, 0}, {0, 2}, {3, 2}, {3, 0}));

    Figure* figure1 = array[0];
    Figure* figure2 = array[1];
    Figure* figure3 = array[2];

    EXPECT_TRUE(dynamic_cast<Square*>(figure1) != nullptr);
    EXPECT_TRUE(dynamic_cast<Rectangle*>(figure2) != nullptr);
    EXPECT_EQ(figure3, nullptr);
}

TEST(ArrayTest, GetAllAreaPolymorphic) {
    Array array;
    array.addFigure(new Square({0, 0}, {0, 2}, {2, 2}, {2, 0}));
    array.addFigure(new Rectangle({0, 0}, {0, 3}, {3, 3}, {3, 0}));
    array.addFigure(new Trapezoid({0, 0}, {2, 0}, {3, 2}, {1, 2}));

    EXPECT_DOUBLE_EQ(array.getAllArea(), 4 + 9 + 4);
}
