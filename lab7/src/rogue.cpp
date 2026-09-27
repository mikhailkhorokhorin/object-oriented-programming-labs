#include "rogue.hpp"

Rogue::Rogue(const std::string& name, const Point& position) : NPC(name, position) {
}

std::string Rogue::getType() const {
    return "Rogue";
}

int Rogue::getMoveDistance() const {
    return MOVE_DISTANCE;
}

int Rogue::getKillDistance() const {
    return KILL_DISTANCE;
}

bool Rogue::kills(const NPC& other) const {
    return other.getType() == "Bear";
}
