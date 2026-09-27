#pragma once

#include "npc.hpp"
#include "visitor.hpp"

class BattleVisitor final : public Visitor {
public:
    explicit BattleVisitor(NPC& defender);

    void visit(Bear& attacker) override;
    void visit(Rogue& attacker) override;
    void visit(Werewolf& attacker) override;

    bool defenderKilled() const;

private:
    NPC* defender_;
    bool defenderKilled_ = false;

    template <typename Attacker>
    void attack();
};

bool kills(NPC& attacker, NPC& defender);
