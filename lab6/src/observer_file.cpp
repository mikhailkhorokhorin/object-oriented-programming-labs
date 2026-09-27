#include "observer_file.hpp"

#include <fstream>
#include <utility>

FileLogger::FileLogger(std::filesystem::path path) : path_(std::move(path)) {
}

void FileLogger::onEvent(const std::string& message) {
    std::ofstream file(path_, std::ios::app);
    file << message << '\n';
}

const std::filesystem::path& FileLogger::getPath() const {
    return path_;
}
