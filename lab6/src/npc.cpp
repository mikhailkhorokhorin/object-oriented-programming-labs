#include "npc.hpp"

NPC::NPC(std::string name, const Point& pos) : name(std::move(name)), position(pos) {
}

const std::string& NPC::getName() const {
    return name;
}

const Point& NPC::getPosition() const {
    return position;
}

double NPC::distanceTo(const NPC& other) const {
    return position.distanceTo(other.position);
}
