#pragma once

#include <algorithm>
#include <mutex>
#include <string>

#include "point.hpp"

class NPC {
   protected:
    std::string name;
    Point position;
    bool alive = true;

    mutable std::mutex mutex;

   public:
    NPC(std::string name, const Point& pos);
    virtual ~NPC() = default;

    virtual std::string getType() const = 0;

    const std::string& getName() const;
    Point getPosition() const;

    double distanceTo(const NPC& other) const;

    bool isAlive() const;
    void kill();

    void move(int dx, int dy, int MAP_WIDTH, int MAP_HEIGHT);

    virtual int getMoveDistance() const = 0;
    virtual int getKillDistance() const = 0;

    virtual bool kills(const NPC& other) const = 0;
};
