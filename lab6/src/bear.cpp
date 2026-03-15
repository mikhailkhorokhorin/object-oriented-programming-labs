#include "bear.hpp"

#include "visitor.hpp"

Bear::Bear(const std::string& name, const Point& pos) : NPC(name, pos) {
}

std::string Bear::getType() const {
    return "Bear";
}

bool Bear::kills(const NPC& other) const {
    return other.getType() == "Werewolf";
}

void Bear::accept(Visitor& visitor, NPC& other) {
    visitor.visit(*this, other);
}
