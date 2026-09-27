#include "npc_factory.hpp"

#include <array>
#include <sstream>
#include <stdexcept>

#include "bear.hpp"
#include "rogue.hpp"
#include "werewolf.hpp"

namespace {

const std::array<std::string, 3> TYPES = {"Bear", "Rogue", "Werewolf"};

}

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

std::shared_ptr<NPC> NPCFactory::createRandom(int id, int mapWidth, int mapHeight,
                                              std::mt19937& engine) {
    if (mapWidth <= 0 || mapHeight <= 0) {
        throw std::invalid_argument("map size must be positive");
    }
    std::uniform_int_distribution<std::size_t> typeDistribution(0, TYPES.size() - 1);
    std::uniform_int_distribution<int> xDistribution(0, mapWidth - 1);
    std::uniform_int_distribution<int> yDistribution(0, mapHeight - 1);
    const std::string& type = TYPES.at(typeDistribution(engine));
    const int x = xDistribution(engine);
    const int y = yDistribution(engine);
    return create(type, type + "_" + std::to_string(id), x, y);
}
