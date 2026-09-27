#include "bear.hpp"

Bear::Bear(const std::string& name, const Point& position) : NPC(name, position) {
}

std::string Bear::getType() const {
    return "Bear";
}

int Bear::getMoveDistance() const {
    return MOVE_DISTANCE;
}

int Bear::getKillDistance() const {
    return KILL_DISTANCE;
}

bool Bear::kills(const NPC& other) const {
    return other.getType() == "Werewolf";
}
