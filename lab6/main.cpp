#include "dungeon.hpp"
#include "npc_factory.hpp"
#include "observer_console.hpp"

int main() {
    ConsoleLogger logger;

    Dungeon dungeon(100.0);
    dungeon.addObserver(&logger);

    NPCFactory factory;
    dungeon.addNPC("Bear", "Baloo", 0, 0);
    dungeon.addNPC("Werewolf", "Lupin", 10, 10);
    dungeon.addNPC("Rogue", "Robin", 5, 5);

    dungeon.battle();

    dungeon.printAll();

    return 0;
}
