#include "observer_console.hpp"

void ConsoleLogger::onEvent(const std::string& message) {
    ThreadSafeCout() << message;
}
