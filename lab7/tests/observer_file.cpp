#include "observer_file.hpp"

#include <gtest/gtest.h>


TEST(FileLoggerTest, OnEventWritesToLogTxt) {
    {
        std::ofstream ofs("log.txt", std::ios::trunc);
    }

    FileLogger logger;
    std::string message = "Test log message";

    logger.onEvent(message);

    std::ifstream ifs("log.txt");
    ASSERT_TRUE(ifs.is_open());

    bool found = false;
    std::string line;
    while (std::getline(ifs, line)) {
        if (line == message) {
            found = true;
            break;
        }
    }

    EXPECT_TRUE(found);
}
