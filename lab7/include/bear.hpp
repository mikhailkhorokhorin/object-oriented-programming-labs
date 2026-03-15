#pragma once

#include "npc.hpp"

class Bear : public NPC {
   public:
    Bear(const std::string& name, const Point& pos);

    std::string getType() const override;

    int getMoveDistance() const override;
    int getKillDistance() const override;

    bool kills(const NPC& other) const override;
};
