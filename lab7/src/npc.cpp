#include "npc.hpp"

#include <algorithm>
#include <utility>

NPC::NPC(std::string name, const Point& position) : name_(std::move(name)), position_(position) {
}

const std::string& NPC::getName() const {
    return name_;
}

Point NPC::getPosition() const {
    const std::lock_guard lock(mutex_);
    return position_;
}

double NPC::distanceTo(const NPC& other) const {
    return getPosition().distanceTo(other.getPosition());
}

bool NPC::isAlive() const {
    const std::lock_guard lock(mutex_);
    return alive_;
}

bool NPC::tryKill() {
    const std::lock_guard lock(mutex_);
    return std::exchange(alive_, false);
}

void NPC::move(int dx, int dy, int mapWidth, int mapHeight) {
    const std::lock_guard lock(mutex_);
    if (!alive_ || mapWidth <= 0 || mapHeight <= 0) {
        return;
    }
    position_ = Point(std::clamp(position_.getX() + dx, 0, mapWidth - 1),
                      std::clamp(position_.getY() + dy, 0, mapHeight - 1));
}
