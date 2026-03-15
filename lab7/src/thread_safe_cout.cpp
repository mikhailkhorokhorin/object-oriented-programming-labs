#include "thread_safe_cout.hpp"

std::mutex ThreadSafeCout::mutex;

ThreadSafeCout::ThreadSafeCout() = default;

ThreadSafeCout::~ThreadSafeCout() {
    std::lock_guard<std::mutex> lock(mutex);
    std::cout << buffer.str() << std::endl;
}
