#include "dungeon.hpp"

Dungeon::Dungeon(double battleRange) : battleVisitor(battleRange) {
}

void Dungeon::addNPC(const std::string& type, const std::string& name, int x, int y) {
    auto npc = NPCFactory::create(type, name, x, y);
    if (npc)
        npcs.push_back(npc);
    else
        std::cerr << "Unknown NPC type: " << type << std::endl;
}

void Dungeon::addObserver(IObserver* observer) {
    battleVisitor.addObserver(observer);
}

void Dungeon::printAll() const {
    for (const auto& npc : npcs) {
        std::cout << npc->getType() << " " << npc->getName() << " (" << npc->getPosition().getX()
                  << ", " << npc->getPosition().getY() << ")" << std::endl;
    }
}

void Dungeon::battle() {
    std::vector<std::shared_ptr<NPC>> alive = npcs;

    for (size_t i = 0; i < alive.size(); ++i) {
        for (size_t j = i + 1; j < alive.size(); ++j) {
            if (!alive[i] || !alive[j])
                continue;
            alive[i]->accept(battleVisitor, *alive[j]);
        }
    }

    alive.erase(std::remove_if(alive.begin(), alive.end(),
                               [](const std::shared_ptr<NPC>& npc) { return !npc; }),
                alive.end());

    npcs = alive;
}

void Dungeon::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open())
        return;

    for (const auto& npc : npcs) {
        file << npc->getType() << " " << npc->getName() << " " << npc->getPosition().getX() << " "
             << npc->getPosition().getY() << std::endl;
    }
}

void Dungeon::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open())
        return;

    npcs.clear();
    std::string line;
    while (std::getline(file, line)) {
        auto npc = NPCFactory::fromString(line);
        if (npc)
            npcs.push_back(npc);
    }
}
