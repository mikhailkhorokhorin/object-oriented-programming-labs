#include "rogue.hpp"

#include "bear.hpp"
#include "gtest/gtest.h"
#include "visitor.hpp"
#include "werewolf.hpp"

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

TEST(RogueTest, ConstructorAndGetType) {
    Point point(5, 10);
    Rogue rogue("Robin", point);
    EXPECT_EQ(rogue.getName(), "Robin");
    EXPECT_EQ(rogue.getType(), "Rogue");
    EXPECT_EQ(rogue.getPosition().getX(), 5);
    EXPECT_EQ(rogue.getPosition().getY(), 10);
}

TEST(RogueTest, KillsLogic) {
    Point point1(0, 0);
    Rogue rogue1("Robin", point1);

    Point point2(1, 1);
    Bear bear1("Baloo", point2);
    Werewolf werewolf1("Lupin", point2);

    EXPECT_TRUE(rogue1.kills(bear1));
    EXPECT_FALSE(rogue1.kills(werewolf1));
    EXPECT_FALSE(rogue1.kills(rogue1));
}

TEST(RogueTest, AcceptVisitor) {
    Point point1(0, 0);
    Rogue rogue1("Robin", point1);

    Point point2(1, 1);
    Bear bear1("Baloo", point2);

    DummyVisitor visitor1;
    rogue1.accept(visitor1, bear1);

    EXPECT_FALSE(visitor1.visitedBear);
    EXPECT_TRUE(visitor1.visitedRogue);
    EXPECT_FALSE(visitor1.visitedWerewolf);
}
