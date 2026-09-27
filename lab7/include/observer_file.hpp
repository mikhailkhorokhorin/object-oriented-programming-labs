#pragma once

#include <filesystem>
#include <mutex>
#include <string>

#include "observer.hpp"

class FileLogger final : public IObserver {
public:
    explicit FileLogger(std::filesystem::path path = "log.txt");

    void onEvent(const std::string& message) override;

    const std::filesystem::path& getPath() const;

private:
    std::filesystem::path path_;
    std::mutex mutex_;
};
