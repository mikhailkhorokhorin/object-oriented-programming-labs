#include "werewolf.hpp"

#include "visitor.hpp"

Werewolf::Werewolf(const std::string& name, const Point& position) : NPC(name, position) {
}

std::string Werewolf::getType() const {
    return "Werewolf";
}

void Werewolf::accept(Visitor& visitor) {
    visitor.visit(*this);
}
