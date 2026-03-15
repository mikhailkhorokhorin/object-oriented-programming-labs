#include <iostream>

#include "array.hpp"
#include "hexagon.hpp"
#include "pentagon.hpp"
#include "rhombus.hpp"

int main() {
    Rhombus<int> rhombus({0, 0}, {2, 1}, {0, 2}, {-2, 1});
    Pentagon<int> pentagon({0, 0}, {2, 0}, {3, 2}, {1, 4}, {-1, 2});
    Hexagon<int> hexagon({0, 0}, {2, 0}, {3, 1}, {2, 2}, {0, 2}, {-1, 1});

    std::cout << "Rhombus: ";
    rhombus.print(std::cout);

    std::cout << "Pentagon: ";
    pentagon.print(std::cout);

    std::cout << "Hexagon: ";
    hexagon.print(std::cout);

    std::cout << std::endl;

    Array<int> array(3);
    array.addFigure(std::make_shared<Rhombus<int>>(rhombus));
    array.addFigure(std::make_shared<Pentagon<int>>(pentagon));
    array.addFigure(std::make_shared<Hexagon<int>>(hexagon));

    array.printFigures();

    std::cout << "Total area: " << array.getAllArea() << std::endl;

    std::cout << std::endl;

    std::shared_ptr<Figure<int>> figure = array[1];
    std::cout << "Figure at index 1: ";
    figure->print(std::cout);
    std::cout << "Area: " << static_cast<double>(*figure) << std::endl;

    return 0;
}
