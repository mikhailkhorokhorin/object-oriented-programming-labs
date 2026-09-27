#include "rogue.hpp"

#include "visitor.hpp"

Rogue::Rogue(const std::string& name, const Point& position) : NPC(name, position) {
}

std::string Rogue::getType() const {
    return "Rogue";
}

void Rogue::accept(Visitor& visitor) {
    visitor.visit(*this);
}
