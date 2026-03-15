#pragma once

#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "battle_visitor.hpp"
#include "npc.hpp"
#include "npc_factory.hpp"
#include "observer.hpp"

class Dungeon {
   private:
    std::vector<std::shared_ptr<NPC>> npcs;
    BattleVisitor battleVisitor;

   public:
    explicit Dungeon(double battleRange = 50.0);

    void addNPC(const std::string& type, const std::string& name, int x, int y);

    void addObserver(IObserver* observer);

    void printAll() const;

    void battle();

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};
