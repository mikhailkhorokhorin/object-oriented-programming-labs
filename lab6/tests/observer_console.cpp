#include "observer_console.hpp"

#include <gtest/gtest.h>

#include <sstream>

TEST(ConsoleLoggerTest, WritesLinePerEvent) {
    std::ostringstream out;
    ConsoleLogger logger(out);
    logger.onEvent("first");
    logger.onEvent("second");
    EXPECT_EQ(out.str(), "first\nsecond\n");
}
