#include "bear.hpp"

#include "visitor.hpp"

Bear::Bear(const std::string& name, const Point& position) : NPC(name, position) {
}

std::string Bear::getType() const {
    return "Bear";
}

void Bear::accept(Visitor& visitor) {
    visitor.visit(*this);
}
