#pragma once

#include <chrono>
#include <cstddef>
#include <functional>
#include <memory>
#include <ostream>
#include <random>
#include <string>
#include <utility>
#include <vector>

#include "npc.hpp"
#include "observer.hpp"
#include "synced_stream.hpp"

struct SimulationTiming {
    std::chrono::milliseconds duration{30000};
    std::chrono::milliseconds moveInterval{100};
    std::chrono::milliseconds printInterval{1000};
};

class Dungeon {
public:
    using Dice = std::function<int()>;
    using Fight = std::pair<std::shared_ptr<NPC>, std::shared_ptr<NPC>>;

    Dungeon(int width, int height, Dice dice, std::size_t queueCapacity);

    void addObserver(IObserver* observer);
    void addNPC(std::shared_ptr<NPC> npc);
    void spawnRandomNPCs(int count, std::mt19937& engine);

    void moveAll(std::mt19937& engine);
    std::vector<Fight> findFights() const;
    void fight(NPC& attacker, NPC& defender);

    void run(const SimulationTiming& timing, SyncedStream& output);

    void printMap(std::ostream& os) const;
    void printSurvivors(std::ostream& os) const;

    std::vector<std::shared_ptr<NPC>> getAliveNPCs() const;
    int getWidth() const;
    int getHeight() const;

private:
    std::vector<std::shared_ptr<NPC>> npcs_;
    std::vector<IObserver*> observers_;
    int width_;
    int height_;
    Dice dice_;
    std::size_t queueCapacity_;

    bool attack(NPC& attacker, NPC& defender);
    void notify(const std::string& message) const;
};
