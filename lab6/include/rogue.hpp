#pragma once

#include "npc.hpp"

class Rogue : public NPC {
   public:
    Rogue(const std::string& name, const Point& pos);

    std::string getType() const override;
    bool kills(const NPC& other) const override;
    void accept(Visitor& v, NPC& other) override;
};
