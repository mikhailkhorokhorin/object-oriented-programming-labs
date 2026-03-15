#include "werewolf.hpp"

#include "visitor.hpp"

Werewolf::Werewolf(const std::string& name, const Point& pos) : NPC(name, pos) {
}

std::string Werewolf::getType() const {
    return "Werewolf";
}

bool Werewolf::kills(const NPC& other) const {
    return other.getType() == "Rogue";
}

void Werewolf::accept(Visitor& v, NPC& other) {
    v.visit(*this, other);
}
