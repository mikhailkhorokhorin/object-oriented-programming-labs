#include "battle_visitor.hpp"

#include "bear.hpp"
#include "npc.hpp"
#include "observer.hpp"
#include "rogue.hpp"
#include "werewolf.hpp"

BattleVisitor::BattleVisitor(double range) : attackRange(range) {
}

void BattleVisitor::addObserver(IObserver* obs) {
    observers.push_back(obs);
}

void BattleVisitor::notify(const std::string& msg) {
    for (auto* o : observers)
        o->onEvent(msg);
}

BattleResult BattleVisitor::resolve(NPC& A, NPC& B) {
    BattleResult result;

    if (A.distanceTo(B) > attackRange)
        return result;

    bool aKills = A.kills(B);

    bool bKills = B.kills(A);

    if (aKills && bKills) {
        result.dead1 = &A;
        result.dead2 = &B;
        notify(A.getName() + " and " + B.getName() + " killed each other");
    } else if (aKills) {
        result.dead2 = &B;
        notify(A.getName() + " killed " + B.getName());
    } else if (bKills) {
        result.dead1 = &A;
        notify(B.getName() + " killed " + A.getName());
    }

    return result;
}

void BattleVisitor::visit(Bear& attacker, NPC& defender) {
    resolve(attacker, defender);
}

void BattleVisitor::visit(Rogue& attacker, NPC& defender) {
    resolve(attacker, defender);
}

void BattleVisitor::visit(Werewolf& attacker, NPC& defender) {
    resolve(attacker, defender);
}
