#include "observer_console.hpp"

#include "gtest/gtest.h"

TEST(ConsoleLoggerTest, OnEventOutputsMessage) {
    ConsoleLogger consoleLogger;

    std::ostringstream outputStream;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(outputStream.rdbuf());

    consoleLogger.onEvent("Test event message");

    std::cout.rdbuf(oldCoutBuffer);

    std::string capturedOutput = outputStream.str();
    EXPECT_EQ(capturedOutput, "Test event message\n");
}
