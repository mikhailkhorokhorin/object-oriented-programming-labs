#pragma once

#include <string>

#include "npc.hpp"

class Rogue final : public NPC {
public:
    static constexpr int MOVE_DISTANCE = 10;
    static constexpr int KILL_DISTANCE = 10;

    Rogue(const std::string& name, const Point& position);

    std::string getType() const override;
    int getMoveDistance() const override;
    int getKillDistance() const override;
    bool kills(const NPC& other) const override;
};
