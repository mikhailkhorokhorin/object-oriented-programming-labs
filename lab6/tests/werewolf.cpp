#include "werewolf.hpp"

#include "bear.hpp"
#include "gtest/gtest.h"
#include "rogue.hpp"
#include "visitor.hpp"

class DummyVisitor : public Visitor {
   public:
    bool visitedBear = false;
    bool visitedRogue = false;
    bool visitedWerewolf = false;

    void visit(Bear& attacker, NPC& defender) override {
        visitedBear = true;
    }
    void visit(Rogue& attacker, NPC& defender) override {
        visitedRogue = true;
    }
    void visit(Werewolf& attacker, NPC& defender) override {
        visitedWerewolf = true;
    }
};

TEST(WerewolfTest, ConstructorAndGetType) {
    Point point(7, 14);
    Werewolf werewolf("Lupin", point);
    EXPECT_EQ(werewolf.getName(), "Lupin");
    EXPECT_EQ(werewolf.getType(), "Werewolf");
    EXPECT_EQ(werewolf.getPosition().getX(), 7);
    EXPECT_EQ(werewolf.getPosition().getY(), 14);
}

TEST(WerewolfTest, KillsLogic) {
    Point point1(0, 0);
    Werewolf werewolf1("Lupin", point1);

    Point point2(1, 1);
    Rogue rogue1("Robin", point2);
    Bear bear1("Baloo", point2);

    EXPECT_TRUE(werewolf1.kills(rogue1));
    EXPECT_FALSE(werewolf1.kills(bear1));
    EXPECT_FALSE(werewolf1.kills(werewolf1));
}

TEST(WerewolfTest, AcceptVisitor) {
    Point point1(0, 0);
    Werewolf werewolf1("Lupin", point1);

    Point point2(1, 1);
    Rogue rogue1("Robin", point2);

    DummyVisitor visitor1;
    werewolf1.accept(visitor1, rogue1);

    EXPECT_FALSE(visitor1.visitedBear);
    EXPECT_FALSE(visitor1.visitedRogue);
    EXPECT_TRUE(visitor1.visitedWerewolf);
}
