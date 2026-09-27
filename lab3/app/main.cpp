#include <exception>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

#include "array.hpp"
#include "rectangle.hpp"
#include "square.hpp"
#include "trapezoid.hpp"

namespace {

std::unique_ptr<Figure> makeFigure(const std::string& type) {
    if (type == "square") {
        return std::make_unique<Square>();
    }
    if (type == "rectangle") {
        return std::make_unique<Rectangle>();
    }
    if (type == "trapezoid") {
        return std::make_unique<Trapezoid>();
    }
    throw std::invalid_argument("unknown figure: " + type);
}

}

int main() {
    try {
        Array array;
        std::string type;
        while (std::cin >> type) {
            auto figure = makeFigure(type);
            if (!(std::cin >> *figure)) {
                throw std::invalid_argument("expected 8 coordinates after " + type);
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
