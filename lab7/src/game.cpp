#include "game.hpp"

#include <random>
#include <sstream>
#include <utility>

Game::Game(const GameConfig& config, std::ostream& os, Dungeon::Dice dice)
    : config_(config),
      output_(os),
      consoleLogger_(output_),
      fileLogger_(config.logPath),
      dungeon_(config.mapWidth, config.mapHeight, std::move(dice), config.queueCapacity) {
    dungeon_.addObserver(&consoleLogger_);
    dungeon_.addObserver(&fileLogger_);
}

void Game::run() {
    std::mt19937 engine(std::random_device{}());
    dungeon_.spawnRandomNPCs(config_.npcCount, engine);
    dungeon_.run(config_.timing, output_);
    std::ostringstream survivors;
    dungeon_.printSurvivors(survivors);
    output_.write(survivors.str());
}

Dungeon& Game::getDungeon() {
    return dungeon_;
}

const GameConfig& Game::getConfig() const {
    return config_;
}
