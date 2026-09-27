#pragma once

#include <mutex>
#include <string>

#include "point.hpp"

class NPC {
public:
    NPC(std::string name, const Point& position);
    virtual ~NPC() = default;
    NPC(const NPC&) = delete;
    NPC& operator=(const NPC&) = delete;

    virtual std::string getType() const = 0;
    virtual int getMoveDistance() const = 0;
    virtual int getKillDistance() const = 0;
    virtual bool kills(const NPC& other) const = 0;

    const std::string& getName() const;
    Point getPosition() const;
    double distanceTo(const NPC& other) const;

    bool isAlive() const;
    bool tryKill();

    void move(int dx, int dy, int mapWidth, int mapHeight);

private:
    std::string name_;
    Point position_;
    bool alive_ = true;
    mutable std::mutex mutex_;
};
