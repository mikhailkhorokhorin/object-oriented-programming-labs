#include "random.hpp"

static thread_local std::mt19937 rng(std::random_device{}());
static thread_local std::uniform_int_distribution<int> dist6(1, 6);

int roll_d6() {
    return dist6(rng);
}
