#include <exception>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

#include "array.hpp"
#include "hexagon.hpp"
#include "pentagon.hpp"
#include "rhombus.hpp"

namespace {

using Coordinate = double;

std::shared_ptr<Figure<Coordinate>> makeFigure(const std::string& type) {
    if (type == "rhombus") {
        return std::make_shared<Rhombus<Coordinate>>();
    }
    if (type == "pentagon") {
        return std::make_shared<Pentagon<Coordinate>>();
    }
    if (type == "hexagon") {
        return std::make_shared<Hexagon<Coordinate>>();
    }
    throw std::invalid_argument("unknown figure: " + type);
}

}

int main() {
    try {
        Array<Coordinate> array;
        std::string type;
        while (std::cin >> type) {
            auto figure = makeFigure(type);
            if (!(std::cin >> *figure)) {
                throw std::invalid_argument("not enough coordinates for " + type);
            }
            array.addFigure(std::move(figure));
        }
        array.printFigures(std::cout);
        std::cout << "Total area: " << array.getAllArea() << '\n';
    } catch (const std::exception& error) {
        std::cerr << "error: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
