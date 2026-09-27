#pragma once

#include <string>

#include "npc.hpp"

class Werewolf final : public NPC {
public:
    Werewolf(const std::string& name, const Point& position);

    std::string getType() const override;
    void accept(Visitor& visitor) override;
};
