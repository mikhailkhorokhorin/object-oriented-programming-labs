#pragma once

#include <memory>
#include <random>
#include <string>

#include "npc.hpp"

class NPCFactory {
public:
    static std::shared_ptr<NPC> create(const std::string& type, const std::string& name, int x,
                                       int y);

    static std::shared_ptr<NPC> fromString(const std::string& line);

    static std::shared_ptr<NPC> createRandom(int id, int mapWidth, int mapHeight,
                                             std::mt19937& engine);
};
