#pragma once

#include <mutex>
#include <ostream>
#include <string>

class SyncedStream {
public:
    explicit SyncedStream(std::ostream& os);

    void write(const std::string& text);
    void writeLine(const std::string& line);

private:
    std::ostream* os_;
    std::mutex mutex_;
};
