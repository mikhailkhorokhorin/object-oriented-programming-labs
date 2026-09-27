#pragma once

#include <cstddef>
#include <filesystem>
#include <iostream>

#include "dungeon.hpp"
#include "observer_console.hpp"
#include "observer_file.hpp"
#include "random.hpp"
#include "synced_stream.hpp"

struct GameConfig {
    int mapWidth = 100;
    int mapHeight = 100;
    int npcCount = 50;
    std::size_t queueCapacity = 1024;
    SimulationTiming timing;
    std::filesystem::path logPath = "log.txt";
};

class Game {
public:
    explicit Game(const GameConfig& config = {}, std::ostream& os = std::cout,
                  Dungeon::Dice dice = rollD6);

    void run();

    Dungeon& getDungeon();
    const GameConfig& getConfig() const;

private:
    GameConfig config_;
    SyncedStream output_;
    ConsoleLogger consoleLogger_;
    FileLogger fileLogger_;
    Dungeon dungeon_;
};
