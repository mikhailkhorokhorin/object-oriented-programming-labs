#include "bear.hpp"

Bear::Bear(const std::string& name, const Point& pos) : NPC(name, pos) {
}

std::string Bear::getType() const {
    return "Bear";
}

int Bear::getMoveDistance() const {
    return 5;
}

int Bear::getKillDistance() const {
    return 10;
}

bool Bear::kills(const NPC& other) const {
    return other.getType() == "Werewolf";
}
