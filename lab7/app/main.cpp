#include <charconv>
#include <chrono>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <system_error>

#include "game.hpp"

namespace {

std::chrono::seconds parseDuration(const std::string& text) {
    int seconds = 0;
    const char* end = text.data() + text.size();
    const auto [parsedEnd, error] = std::from_chars(text.data(), end, seconds);
    if (error != std::errc{} || parsedEnd != end || seconds <= 0) {
        throw std::invalid_argument("duration must be a positive number of seconds: " + text);
    }
    return std::chrono::seconds(seconds);
}

}

int main(int argc, char* argv[]) {
    try {
        GameConfig config;
        if (argc > 1) {
            config.timing.duration = parseDuration(argv[1]);
        }
        Game game(config);
        game.run();
    } catch (const std::exception& error) {
        std::cerr << "error: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
