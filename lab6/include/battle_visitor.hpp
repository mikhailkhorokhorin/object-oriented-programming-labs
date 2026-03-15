#pragma once

#include <cmath>
#include <string>
#include <vector>

#include "visitor.hpp"

class IObserver;

struct BattleResult {
    NPC* dead1 = nullptr;
    NPC* dead2 = nullptr;
};

class BattleVisitor : public Visitor {
   private:
    double attackRange;
    std::vector<IObserver*> observers;

    void notify(const std::string& msg);

   public:
    explicit BattleVisitor(double range);

    void addObserver(IObserver* obs);

    void visit(Bear& attacker, NPC& defender) override;
    void visit(Rogue& attacker, NPC& defender) override;
    void visit(Werewolf& attacker, NPC& defender) override;

   private:
    BattleResult resolve(NPC& attacker, NPC& defender);
};
