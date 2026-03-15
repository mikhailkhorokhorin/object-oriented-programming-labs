#include "thread_safe_cout.hpp"

#include <gtest/gtest.h>

TEST(ThreadSafeCoutTest, PrintsBufferOnDestruction) {
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    {
        ThreadSafeCout ts;
        ts << "Hello, " << "World!";
    }

    std::cout.rdbuf(oldCout);

    std::string output = buffer.str();
    EXPECT_NE(output.find("Hello, World!"), std::string::npos);
}
