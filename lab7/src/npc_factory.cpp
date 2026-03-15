#include "npc_factory.hpp"

#include "bear.hpp"
#include "rogue.hpp"
#include "werewolf.hpp"

std::shared_ptr<NPC> NPCFactory::create(const std::string& type, const std::string& name, int x,
                                        int y) {
    if (type == "Bear")
        return std::make_shared<Bear>(name, Point(x, y));
    if (type == "Rogue")
        return std::make_shared<Rogue>(name, Point(x, y));
    if (type == "Werewolf")
        return std::make_shared<Werewolf>(name, Point(x, y));
    return nullptr;
}

std::shared_ptr<NPC> NPCFactory::fromString(const std::string& line) {
    std::stringstream ss(line);
    std::string type, name;
    int x, y;
    ss >> type >> name >> x >> y;
    return create(type, name, x, y);
}

std::shared_ptr<NPC> NPCFactory::createRandom(int MAP_WIDTH, int MAP_HEIGHT) {
    static std::vector<std::string> types = {"Bear", "Rogue", "Werewolf"};
    int idx = rand() % types.size();
    int x = rand() % MAP_WIDTH;
    int y = rand() % MAP_HEIGHT;
    std::string name = types[idx] + "_" + std::to_string(rand() % 1000);
    return create(types[idx], name, x, y);
}
