#pragma once

#include <cstdlib>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

class NPC;

class NPCFactory {
   public:
    static std::shared_ptr<NPC> create(const std::string& type, const std::string& name, int x,
                                       int y);

    static std::shared_ptr<NPC> fromString(const std::string& line);

    static std::shared_ptr<NPC> createRandom(int MAP_WIDTH, int MAP_HEIGHT);
};
