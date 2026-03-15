#include <iostream>

#include "bear.hpp"
#include "game.hpp"
#include "rogue.hpp"
#include "werewolf.hpp"

int main() {
    Game game(100, 100);

    game.init(10);

    std::cout << "=== Starting ===" << std::endl;

    game.run(5);

    auto& dungeon = game.getDungeon();
    auto survivors = dungeon.getAliveNPCs();

    std::cout << "=== Survivors ===" << std::endl;
    for (auto& npc : survivors) {
        auto pos = npc->getPosition();
        std::cout << npc->getType() << " " << npc->getName() << " (" << pos.getX() << ","
                  << pos.getY() << ")" << std::endl;
    }

    return 0;
}
