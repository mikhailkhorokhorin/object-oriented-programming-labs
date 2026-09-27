#include "observer_console.hpp"

ConsoleLogger::ConsoleLogger(SyncedStream& output) : output_(&output) {
}

void ConsoleLogger::onEvent(const std::string& message) {
    output_->writeLine(message);
}
