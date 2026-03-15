#include "werewolf.hpp"

Werewolf::Werewolf(const std::string& name, const Point& pos) : NPC(name, pos) {
}

std::string Werewolf::getType() const {
    return "Werewolf";
}

int Werewolf::getMoveDistance() const {
    return 40;
}

int Werewolf::getKillDistance() const {
    return 5;
}

bool Werewolf::kills(const NPC& other) const {
    return other.getType() == "Rogue";
}
