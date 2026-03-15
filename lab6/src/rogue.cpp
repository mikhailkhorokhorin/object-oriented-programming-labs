#include "rogue.hpp"

#include "visitor.hpp"

Rogue::Rogue(const std::string& name, const Point& pos) : NPC(name, pos) {
}

std::string Rogue::getType() const {
    return "Rogue";
}

bool Rogue::kills(const NPC& other) const {
    return other.getType() == "Bear";
}

void Rogue::accept(Visitor& v, NPC& other) {
    v.visit(*this, other);
}
