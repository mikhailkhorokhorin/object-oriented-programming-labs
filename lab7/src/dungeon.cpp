#include "dungeon.hpp"

#include <algorithm>
#include <condition_variable>
#include <iterator>
#include <mutex>
#include <sstream>
#include <stdexcept>
#include <stop_token>
#include <thread>

#include "npc_factory.hpp"
#include "task_queue.hpp"

namespace {

void waitFor(const std::stop_token& stopToken, std::chrono::milliseconds duration) {
    std::mutex mutex;
    std::condition_variable_any condition;
    std::unique_lock lock(mutex);
    condition.wait_for(lock, stopToken, duration, [] { return false; });
}

void printNPC(std::ostream& os, const NPC& npc) {
    const Point position = npc.getPosition();
    os << npc.getType() << " " << npc.getName() << " (" << position.getX() << ", "
       << position.getY() << ")\n";
}

}

Dungeon::Dungeon(int width, int height, Dice dice, std::size_t queueCapacity)
    : width_(width), height_(height), dice_(std::move(dice)), queueCapacity_(queueCapacity) {
    if (width_ <= 0 || height_ <= 0) {
        throw std::invalid_argument("map size must be positive");
    }
    if (!dice_) {
        throw std::invalid_argument("dice must be set");
    }
}

void Dungeon::addObserver(IObserver* observer) {
    if (observer != nullptr) {
        observers_.push_back(observer);
    }
}

void Dungeon::addNPC(std::shared_ptr<NPC> npc) {
    if (npc) {
        npcs_.push_back(std::move(npc));
    }
}

void Dungeon::spawnRandomNPCs(int count, std::mt19937& engine) {
    for (int i = 0; i < count; ++i) {
        const int id = static_cast<int>(npcs_.size()) + 1;
        addNPC(NPCFactory::createRandom(id, width_, height_, engine));
    }
}

void Dungeon::moveAll(std::mt19937& engine) {
    for (const auto& npc : npcs_) {
        const int step = npc->getMoveDistance();
        std::uniform_int_distribution<int> offset(-step, step);
        int dx = 0;
        int dy = 0;
        do {
            dx = offset(engine);
            dy = offset(engine);
        } while (dx * dx + dy * dy > step * step);
        npc->move(dx, dy, width_, height_);
    }
}

std::vector<Dungeon::Fight> Dungeon::findFights() const {
    std::vector<Fight> fights;
    for (std::size_t i = 0; i < npcs_.size(); ++i) {
        const NPC& first = *npcs_[i];
        if (!first.isAlive()) {
            continue;
        }
        for (std::size_t j = i + 1; j < npcs_.size(); ++j) {
            const NPC& second = *npcs_[j];
            if (!second.isAlive()) {
                continue;
            }
            const double distance = first.distanceTo(second);
            const bool firstReaches = first.kills(second) && distance <= first.getKillDistance();
            const bool secondReaches = second.kills(first) && distance <= second.getKillDistance();
            if (firstReaches || secondReaches) {
                fights.emplace_back(npcs_[i], npcs_[j]);
            }
        }
    }
    return fights;
}

bool Dungeon::attack(NPC& attacker, NPC& defender) {
    if (!attacker.isAlive() || !attacker.kills(defender) ||
        attacker.distanceTo(defender) > attacker.getKillDistance()) {
        return false;
    }
    const int attackRoll = dice_();
    const int defenseRoll = dice_();
    if (attackRoll > defenseRoll && defender.tryKill()) {
        notify(attacker.getName() + " killed " + defender.getName());
        return true;
    }
    return false;
}

void Dungeon::fight(NPC& attacker, NPC& defender) {
    if (!attack(attacker, defender)) {
        attack(defender, attacker);
    }
}

void Dungeon::notify(const std::string& message) const {
    for (IObserver* observer : observers_) {
        observer->onEvent(message);
    }
}

void Dungeon::run(const SimulationTiming& timing, SyncedStream& output) {
    TaskQueue queue(queueCapacity_);
    std::jthread mover([this, &queue, &timing](const std::stop_token& stopToken) {
        std::mt19937 engine(std::random_device{}());
        while (!stopToken.stop_requested()) {
            moveAll(engine);
            for (const auto& [first, second] : findFights()) {
                if (!queue.push([this, first, second] { fight(*first, *second); }, stopToken)) {
                    return;
                }
            }
            waitFor(stopToken, timing.moveInterval);
        }
    });
    std::jthread fighter([&queue](const std::stop_token& stopToken) {
        while (auto task = queue.pop(stopToken)) {
            (*task)();
        }
    });

    const auto deadline = std::chrono::steady_clock::now() + timing.duration;
    while (std::chrono::steady_clock::now() < deadline) {
        std::ostringstream map;
        printMap(map);
        output.write(map.str());
        std::this_thread::sleep_until(
            std::min(deadline, std::chrono::steady_clock::now() + timing.printInterval));
    }
    mover.request_stop();
    fighter.request_stop();
}

void Dungeon::printMap(std::ostream& os) const {
    const auto alive = getAliveNPCs();
    os << "=== Map (" << alive.size() << " alive) ===\n";
    for (const auto& npc : alive) {
        printNPC(os, *npc);
    }
}

void Dungeon::printSurvivors(std::ostream& os) const {
    const auto alive = getAliveNPCs();
    os << "=== Survivors (" << alive.size() << ") ===\n";
    for (const auto& npc : alive) {
        printNPC(os, *npc);
    }
}

std::vector<std::shared_ptr<NPC>> Dungeon::getAliveNPCs() const {
    std::vector<std::shared_ptr<NPC>> alive;
    std::ranges::copy_if(npcs_, std::back_inserter(alive),
                         [](const std::shared_ptr<NPC>& npc) { return npc->isAlive(); });
    return alive;
}

int Dungeon::getWidth() const {
    return width_;
}

int Dungeon::getHeight() const {
    return height_;
}
