#include "observer_console.hpp"

#include <gtest/gtest.h>

TEST(ConsoleLoggerTest, OnEventOutputsMessage) {
    ConsoleLogger logger;

    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    std::string message = "Hello, World!";
    logger.onEvent(message);

    std::cout.rdbuf(oldCout);

    std::string output = buffer.str();

    EXPECT_NE(output.find(message), std::string::npos);
}
