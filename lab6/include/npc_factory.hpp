#pragma once

#include <memory>
#include <string>

#include "npc.hpp"

class NPCFactory {
public:
    static std::shared_ptr<NPC> create(const std::string& type, const std::string& name, int x,
                                       int y);

    static std::shared_ptr<NPC> fromString(const std::string& line);
};
