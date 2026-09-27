#include "werewolf.hpp"

Werewolf::Werewolf(const std::string& name, const Point& position) : NPC(name, position) {
}

std::string Werewolf::getType() const {
    return "Werewolf";
}

int Werewolf::getMoveDistance() const {
    return MOVE_DISTANCE;
}

int Werewolf::getKillDistance() const {
    return KILL_DISTANCE;
}

bool Werewolf::kills(const NPC& other) const {
    return other.getType() == "Rogue";
}
