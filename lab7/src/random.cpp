#include "random.hpp"

#include <random>

namespace {

thread_local std::mt19937 engine{std::random_device{}()};

}

int rollD6() {
    std::uniform_int_distribution<int> distribution(1, 6);
    return distribution(engine);
}
