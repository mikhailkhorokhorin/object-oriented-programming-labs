#pragma once

#include <cstddef>
#include <filesystem>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "npc.hpp"
#include "observer.hpp"

class Dungeon {
public:
    static constexpr int MAP_SIZE = 500;

    bool addNPC(const std::string& type, const std::string& name, int x, int y);
    bool addNPC(std::shared_ptr<NPC> npc);

    void addObserver(IObserver* observer);

    void printAll(std::ostream& os = std::cout) const;

    std::size_t battle(double range);

    const std::vector<std::shared_ptr<NPC>>& getNPCs() const;

    void saveToFile(const std::filesystem::path& path) const;
    void loadFromFile(const std::filesystem::path& path);

private:
    std::vector<std::shared_ptr<NPC>> npcs_;
    std::vector<IObserver*> observers_;

    void notify(const std::string& message) const;
    static bool isOnMap(const Point& position);
};
