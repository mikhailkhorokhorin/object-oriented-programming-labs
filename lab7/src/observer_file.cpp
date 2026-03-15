#include "observer_file.hpp"

void FileLogger::onEvent(const std::string& message) {
    std::lock_guard<std::mutex> lock(mutex);
    std::ofstream file("log.txt", std::ios::app);
    if (file.is_open())
        file << message << std::endl;
}
