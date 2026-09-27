#include "battle_visitor.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "bear.hpp"
#include "rogue.hpp"
#include "werewolf.hpp"

namespace {

std::vector<std::unique_ptr<NPC>> makeAll() {
    std::vector<std::unique_ptr<NPC>> npcs;
    npcs.push_back(std::make_unique<Bear>("Bear", Point()));
    npcs.push_back(std::make_unique<Rogue>("Rogue", Point()));
    npcs.push_back(std::make_unique<Werewolf>("Werewolf", Point()));
    return npcs;
}

}

TEST(BattleVisitorTest, KillMatrix) {
    const auto npcs = makeAll();
    const std::vector<std::pair<std::string, std::string>> expected = {
        {"Bear", "Werewolf"}, {"Werewolf", "Rogue"}, {"Rogue", "Bear"}};
    for (const auto& attacker : npcs) {
        for (const auto& defender : npcs) {
            const bool shouldKill =
                std::find(expected.begin(), expected.end(),
                          std::make_pair(attacker->getType(), defender->getType())) !=
                expected.end();
            EXPECT_EQ(kills(*attacker, *defender), shouldKill)
                << attacker->getType() << " vs " << defender->getType();
        }
    }
}

TEST(BattleVisitorTest, RecordsResultForDefender) {
    Bear bear("Baloo", Point());
    Werewolf werewolf("Lupin", Point());
    BattleVisitor visitor(werewolf);
    EXPECT_FALSE(visitor.defenderKilled());
    bear.accept(visitor);
    EXPECT_TRUE(visitor.defenderKilled());

    BattleVisitor reverse(bear);
    werewolf.accept(reverse);
    EXPECT_FALSE(reverse.defenderKilled());
}
