#include "npc.hpp"

NPC::NPC(std::string name, const Point& pos) : name(std::move(name)), position(pos) {
}

const std::string& NPC::getName() const {
    return name;
}

Point NPC::getPosition() const {
    std::lock_guard<std::mutex> lock(mutex);
    return position;
}

double NPC::distanceTo(const NPC& other) const {
    Point otherPos = other.getPosition();
    std::lock_guard<std::mutex> lock(mutex);
    return position.distanceTo(otherPos);
}

bool NPC::isAlive() const {
    std::lock_guard<std::mutex> lock(mutex);
    return alive;
}

void NPC::kill() {
    std::lock_guard<std::mutex> lock(mutex);
    alive = false;
}

void NPC::move(int dx, int dy, int MAP_WIDTH, int MAP_HEIGHT) {
    std::lock_guard<std::mutex> lock(mutex);
    if (!alive)
        return;

    int x = std::clamp(position.getX() + dx, 0, MAP_WIDTH);
    int y = std::clamp(position.getY() + dy, 0, MAP_HEIGHT);

    position = Point(x, y);
}
