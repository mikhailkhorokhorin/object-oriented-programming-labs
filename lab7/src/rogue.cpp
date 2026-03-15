#include "rogue.hpp"

Rogue::Rogue(const std::string& name, const Point& pos) : NPC(name, pos) {}

std::string Rogue::getType() const {
    return "Rogue";
}

int Rogue::getMoveDistance() const {
    return 10;
}

int Rogue::getKillDistance() const {
    return 10;
}

bool Rogue::kills(const NPC& other) const {
    return other.getType() == "Bear";
}
