#include "game.hpp"

Game::Game(int mapWidth, int mapHeight) : dungeon(mapWidth, mapHeight) {
}

void Game::init(int npcCount) {
    dungeon.addObserver(&consoleLogger);
    dungeon.addObserver(&fileLogger);

    dungeon.spawnRandomNPCs(npcCount);
}

void Game::run(int durationSeconds) {
    dungeon.startSimulation(durationSeconds);
}

Dungeon& Game::getDungeon() {
    return dungeon;
}