#include "dungeon.hpp"

#include <fstream>
#include <stdexcept>
#include <utility>

#include "battle_visitor.hpp"
#include "npc_factory.hpp"

bool Dungeon::addNPC(const std::string& type, const std::string& name, int x, int y) {
    return addNPC(NPCFactory::create(type, name, x, y));
}

bool Dungeon::addNPC(std::shared_ptr<NPC> npc) {
    if (!npc) {
        return false;
    }
    if (!isOnMap(npc->getPosition())) {
        return false;
    }
    npcs_.push_back(std::move(npc));
    return true;
}

bool Dungeon::isOnMap(const Point& position) {
    return position.getX() >= 0 && position.getX() <= MAP_SIZE && position.getY() >= 0 &&
           position.getY() <= MAP_SIZE;
}

void Dungeon::addObserver(IObserver* observer) {
    if (observer != nullptr) {
        observers_.push_back(observer);
    }
}

void Dungeon::notify(const std::string& message) const {
    for (IObserver* observer : observers_) {
        observer->onEvent(message);
    }
}

void Dungeon::printAll(std::ostream& os) const {
    for (const auto& npc : npcs_) {
        os << npc->getType() << " " << npc->getName() << " (" << npc->getPosition().getX() << ", "
           << npc->getPosition().getY() << ")\n";
    }
}

std::size_t Dungeon::battle(double range) {
    std::vector<bool> dead(npcs_.size(), false);
    for (std::size_t i = 0; i < npcs_.size(); ++i) {
        for (std::size_t j = i + 1; j < npcs_.size(); ++j) {
            if (dead[i] || dead[j] || npcs_[i]->distanceTo(*npcs_[j]) > range) {
                continue;
            }
            NPC& first = *npcs_[i];
            NPC& second = *npcs_[j];
            const bool firstWins = kills(first, second);
            const bool secondWins = kills(second, first);
            if (firstWins) {
                dead[j] = true;
                notify(first.getName() + " killed " + second.getName());
            }
            if (secondWins) {
                dead[i] = true;
                notify(second.getName() + " killed " + first.getName());
            }
        }
    }
    std::vector<std::shared_ptr<NPC>> survivors;
    for (std::size_t i = 0; i < npcs_.size(); ++i) {
        if (!dead[i]) {
            survivors.push_back(npcs_[i]);
        }
    }
    const std::size_t killed = npcs_.size() - survivors.size();
    npcs_ = std::move(survivors);
    return killed;
}

const std::vector<std::shared_ptr<NPC>>& Dungeon::getNPCs() const {
    return npcs_;
}

void Dungeon::saveToFile(const std::filesystem::path& path) const {
    std::ofstream file(path);
    if (!file) {
        throw std::runtime_error("cannot write " + path.string());
    }
    for (const auto& npc : npcs_) {
        file << npc->getType() << " " << npc->getName() << " " << npc->getPosition().getX() << " "
             << npc->getPosition().getY() << '\n';
    }
}

void Dungeon::loadFromFile(const std::filesystem::path& path) {
    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error("cannot read " + path.string());
    }
    std::vector<std::shared_ptr<NPC>> loaded;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        auto npc = NPCFactory::fromString(line);
        if (!npc) {
            throw std::runtime_error("invalid NPC line: " + line);
        }
        if (!isOnMap(npc->getPosition())) {
            throw std::runtime_error("NPC outside the map: " + line);
        }
        loaded.push_back(std::move(npc));
    }
    npcs_ = std::move(loaded);
}
