#include "observer_console.hpp"

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "synced_stream.hpp"

TEST(ConsoleLoggerTest, WritesLinePerEvent) {
    std::ostringstream out;
    SyncedStream stream(out);
    ConsoleLogger logger(stream);
    logger.onEvent("first");
    logger.onEvent("second");
    EXPECT_EQ(out.str(), "first\nsecond\n");
}

TEST(SyncedStreamTest, ConcurrentLinesAreNotInterleaved) {
    std::ostringstream out;
    SyncedStream stream(out);
    const std::string line(64, 'x');
    {
        std::vector<std::jthread> threads;
        for (int t = 0; t < 4; ++t) {
            threads.emplace_back([&stream, &line] {
                for (int i = 0; i < 100; ++i) {
                    stream.writeLine(line);
                }
            });
        }
    }
    std::istringstream in(out.str());
    std::string read;
    int lines = 0;
    while (std::getline(in, read)) {
        EXPECT_EQ(read, line);
        ++lines;
    }
    EXPECT_EQ(lines, 400);
}
