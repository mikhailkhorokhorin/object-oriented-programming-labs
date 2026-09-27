#include "battle_visitor.hpp"

#include <type_traits>

#include "bear.hpp"
#include "rogue.hpp"
#include "werewolf.hpp"

namespace {

template <typename Attacker, typename Defender>
constexpr bool KILLS = (std::is_same_v<Attacker, Bear> && std::is_same_v<Defender, Werewolf>) ||
                       (std::is_same_v<Attacker, Werewolf> && std::is_same_v<Defender, Rogue>) ||
                       (std::is_same_v<Attacker, Rogue> && std::is_same_v<Defender, Bear>);

template <typename Attacker>
class DefenderVisitor final : public Visitor {
public:
    void visit(Bear&) override { killed_ = KILLS<Attacker, Bear>; }
    void visit(Rogue&) override { killed_ = KILLS<Attacker, Rogue>; }
    void visit(Werewolf&) override { killed_ = KILLS<Attacker, Werewolf>; }

    bool killed() const { return killed_; }

private:
    bool killed_ = false;
};

}

BattleVisitor::BattleVisitor(NPC& defender) : defender_(&defender) {
}

template <typename Attacker>
void BattleVisitor::attack() {
    DefenderVisitor<Attacker> visitor;
    defender_->accept(visitor);
    defenderKilled_ = visitor.killed();
}

void BattleVisitor::visit(Bear&) {
    attack<Bear>();
}

void BattleVisitor::visit(Rogue&) {
    attack<Rogue>();
}

void BattleVisitor::visit(Werewolf&) {
    attack<Werewolf>();
}

bool BattleVisitor::defenderKilled() const {
    return defenderKilled_;
}

bool kills(NPC& attacker, NPC& defender) {
    BattleVisitor visitor(defender);
    attacker.accept(visitor);
    return visitor.defenderKilled();
}
