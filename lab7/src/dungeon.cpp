#include "dungeon.hpp"

#include "thread_safe_cout.hpp"

Dungeon::Dungeon(int width, int height) : MAP_WIDTH(width), MAP_HEIGHT(height) {
}

void Dungeon::addObserver(IObserver* observer) {
    observers.push_back(observer);
}

void Dungeon::notifyObservers(const std::string& message) {
    for (auto* obs : observers)
        obs->onEvent(message);
}

void Dungeon::spawnRandomNPCs(int count) {
    for (int i = 0; i < count; ++i)
        npcs.push_back(NPCFactory::createRandom(MAP_WIDTH, MAP_HEIGHT));
}

std::vector<std::shared_ptr<NPC>> Dungeon::getAliveNPCs() const {
    std::vector<std::shared_ptr<NPC>> alive;
    for (auto& npc : npcs)
        if (npc->isAlive())
            alive.push_back(npc);

    return alive;
}

void Dungeon::printMap() const {
    ThreadSafeCout ts;
    ts << "\n=== Map ===\n";
    for (auto& npc : npcs) {
        if (!npc->isAlive())
            continue;
        auto pos = npc->getPosition();
        ts << npc->getType() << " " << npc->getName() << " (" << pos.getX() << "," << pos.getY()
           << ")\n";
    }
    ts << "\n";
}

void Dungeon::startSimulation(int durationSeconds) {
    running = true;

    std::thread movementThread([this]() {
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dx(-1, 1);
        std::uniform_int_distribution<int> dy(-1, 1);

        while (running) {
            for (auto& npc : npcs) {
                if (!npc->isAlive())
                    continue;

                int mx = dx(rng) * npc->getMoveDistance();
                int my = dy(rng) * npc->getMoveDistance();
                npc->move(mx, my, MAP_WIDTH, MAP_HEIGHT);

                for (auto& other : npcs) {
                    if (npc == other || !other->isAlive())
                        continue;
                    if (npc->distanceTo(*other) <=
                        std::max(npc->getKillDistance(), other->getKillDistance())) {
                        battleQueue.push([npc, other, this]() {
                            if (!npc->isAlive() || !other->isAlive())
                                return;

                            int attack = rand() % 6 + 1;
                            int defense = rand() % 6 + 1;

                            if (npc->kills(*other) && attack > defense) {
                                other->kill();
                                notifyObservers(npc->getName() + " killed " + other->getName());
                            } else if (other->kills(*npc) && defense > attack) {
                                npc->kill();
                                notifyObservers(other->getName() + " killed " + npc->getName());
                            }
                        });
                    }
                }
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    });

    std::thread battleThread([this]() {
        while (running) {
            battleQueue.executeAll();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });

    auto startTime = std::chrono::steady_clock::now();
    while (std::chrono::steady_clock::now() - startTime < std::chrono::seconds(durationSeconds)) {
        printMap();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    running = false;
    movementThread.join();
    battleThread.join();

    ThreadSafeCout() << "=== Survivors ===";
    for (auto& npc : getAliveNPCs()) {
        auto pos = npc->getPosition();
        ThreadSafeCout() << npc->getType() << " " << npc->getName() << " (" << pos.getX() << ","
                         << pos.getY() << ")\n";
    }
}

void Dungeon::addNPCInstance(std::shared_ptr<NPC> npc) {
    npcs.push_back(npc);
}