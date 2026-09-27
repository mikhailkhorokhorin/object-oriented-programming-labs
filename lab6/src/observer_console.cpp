#include "observer_console.hpp"

ConsoleLogger::ConsoleLogger(std::ostream& os) : os_(&os) {
}

void ConsoleLogger::onEvent(const std::string& message) {
    *os_ << message << '\n';
}
