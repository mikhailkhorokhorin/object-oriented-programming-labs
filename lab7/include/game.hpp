#pragma once

#include <memory>

#include "dungeon.hpp"
#include "observer_console.hpp"
#include "observer_file.hpp"

class Game {
   private:
    Dungeon dungeon;

    ConsoleLogger consoleLogger;
    FileLogger fileLogger;

   public:
    Game(int mapWidth = 100, int mapHeight = 100);

    void init(int npcCount = 50);

    void run(int durationSeconds = 30);

    Dungeon& getDungeon();
};
