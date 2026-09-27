#include "npc_factory.hpp"

#include <sstream>

#include "bear.hpp"
#include "rogue.hpp"
#include "werewolf.hpp"

std::shared_ptr<NPC> NPCFactory::create(const std::string& type, const std::string& name, int x,
                                        int y) {
    const Point position(x, y);
    if (type == "Bear") {
        return std::make_shared<Bear>(name, position);
    }
    if (type == "Rogue") {
        return std::make_shared<Rogue>(name, position);
    }
    if (type == "Werewolf") {
        return std::make_shared<Werewolf>(name, position);
    }
    return nullptr;
}

std::shared_ptr<NPC> NPCFactory::fromString(const std::string& line) {
    std::istringstream stream(line);
    std::string type;
    std::string name;
    int x = 0;
    int y = 0;
    if (!(stream >> type >> name >> x >> y)) {
        return nullptr;
    }
    return create(type, name, x, y);
}
