#include "battle_visitor.hpp"

#include "bear.hpp"
#include "gtest/gtest.h"
#include "observer.hpp"
#include "point.hpp"
#include "rogue.hpp"
#include "werewolf.hpp"

class DummyObserver : public IObserver {
   public:
    std::vector<std::string> messages;

    void onEvent(const std::string& msg) override {
        messages.push_back(msg);
    }
};

TEST(BattleVisitorTest, BearKillsWerewolf) {
    Point pointBear(0, 0);
    Point pointWerewolf(10, 10);

    Bear bear("Baloo", pointBear);
    Werewolf werewolf("Lupin", pointWerewolf);

    DummyObserver observer;
    BattleVisitor visitor(50.0);
    visitor.addObserver(&observer);

    bear.accept(visitor, werewolf);

    ASSERT_EQ(observer.messages.size(), 1);
    EXPECT_EQ(observer.messages[0], "Baloo killed Lupin");
}

TEST(BattleVisitorTest, RogueKillsBear) {
    Point pointRogue(0, 0);
    Point pointBear(10, 10);

    Rogue rogue("Robin", pointRogue);
    Bear bear("Baloo", pointBear);

    DummyObserver observer;
    BattleVisitor visitor(50.0);
    visitor.addObserver(&observer);

    rogue.accept(visitor, bear);

    ASSERT_EQ(observer.messages.size(), 1);
    EXPECT_EQ(observer.messages[0], "Robin killed Baloo");
}

TEST(BattleVisitorTest, WerewolfKillsRogue) {
    Point pointWerewolf(0, 0);
    Point pointRogue(10, 10);

    Werewolf werewolf("Lupin", pointWerewolf);
    Rogue rogue("Robin", pointRogue);

    DummyObserver observer;
    BattleVisitor visitor(50.0);
    visitor.addObserver(&observer);

    werewolf.accept(visitor, rogue);

    ASSERT_EQ(observer.messages.size(), 1);
    EXPECT_EQ(observer.messages[0], "Lupin killed Robin");
}

TEST(BattleVisitorTest, NoKillOutOfRange) {
    Point pointBear(0, 0);
    Point pointRogue(100, 100);

    Bear bear("Baloo", pointBear);
    Rogue rogue("Robin", pointRogue);

    DummyObserver observer;
    BattleVisitor visitor(50.0);
    visitor.addObserver(&observer);

    bear.accept(visitor, rogue);

    EXPECT_TRUE(observer.messages.empty());
}
