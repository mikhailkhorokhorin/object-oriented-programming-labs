#pragma once

#include <string>

#include "point.hpp"

class Visitor;

class NPC {
public:
    NPC(std::string name, const Point& position);
    virtual ~NPC() = default;

    virtual std::string getType() const = 0;
    virtual void accept(Visitor& visitor) = 0;

    const std::string& getName() const;
    const Point& getPosition() const;

    double distanceTo(const NPC& other) const;

private:
    std::string name_;
    Point position_;
};
