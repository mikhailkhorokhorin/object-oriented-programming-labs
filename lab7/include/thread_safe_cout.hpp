#pragma once

#ifndef THREAD_SAFE_COUT_HPP
#define THREAD_SAFE_COUT_HPP
#include <iostream>
#include <mutex>
#include <sstream>

class ThreadSafeCout {
   public:
    ThreadSafeCout();
    ~ThreadSafeCout();

    template <typename T>
    ThreadSafeCout& operator<<(const T& value);

   private:
    static std::mutex mutex;
    std::ostringstream buffer;
};

template <typename T>
ThreadSafeCout& ThreadSafeCout::operator<<(const T& value) {
    buffer << value;
    return *this;
}

#endif
