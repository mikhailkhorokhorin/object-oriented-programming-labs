#include "npc.hpp"

#include <utility>

NPC::NPC(std::string name, const Point& position) : name_(std::move(name)), position_(position) {
}

const std::string& NPC::getName() const {
    return name_;
}

const Point& NPC::getPosition() const {
    return position_;
}

double NPC::distanceTo(const NPC& other) const {
    return position_.distanceTo(other.position_);
}
