#pragma once

#include <atomic>
#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <thread>
#include <vector>

#include "npc.hpp"
#include "npc_factory.hpp"
#include "observer.hpp"
#include "task_queue.hpp"

class Dungeon {
   private:
    std::vector<std::shared_ptr<NPC>> npcs;
    std::vector<IObserver*> observers;

    TaskQueue battleQueue;
    std::atomic<bool> running{false};

    int MAP_WIDTH;
    int MAP_HEIGHT;

   public:
    Dungeon(int width = 100, int height = 100);

    void addObserver(IObserver* observer);

    void spawnRandomNPCs(int count);

    void startSimulation(int durationSeconds);

    void printMap() const;

    std::vector<std::shared_ptr<NPC>> getAliveNPCs() const;

    void notifyObservers(const std::string& message);
    void addNPCInstance(std::shared_ptr<NPC> npc);
};
