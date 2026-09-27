#pragma once

#include <string>

#include "npc.hpp"

class Rogue final : public NPC {
public:
    Rogue(const std::string& name, const Point& position);

    std::string getType() const override;
    void accept(Visitor& visitor) override;
};
