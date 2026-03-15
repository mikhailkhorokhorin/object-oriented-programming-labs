#include "observer_console.hpp"

void ConsoleLogger::onEvent(const std::string& msg) {
    std::cout << msg << std::endl;
}
