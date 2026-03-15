#pragma once

#include <string>

#include "point.hpp"

class Visitor;

class NPC {
   protected:
    std::string name;
    Point position;

   public:
    NPC(std::string name, const Point& pos);
    virtual ~NPC() = default;

    virtual std::string getType() const = 0;

    const std::string& getName() const;
    const Point& getPosition() const;

    double distanceTo(const NPC& other) const;

    virtual bool kills(const NPC& other) const = 0;
    virtual void accept(Visitor& visitor, NPC& other) = 0;
};
