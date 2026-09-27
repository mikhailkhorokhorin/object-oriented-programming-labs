#pragma once

#include <string>

#include "npc.hpp"

class Bear final : public NPC {
public:
    Bear(const std::string& name, const Point& position);

    std::string getType() const override;
    void accept(Visitor& visitor) override;
};
