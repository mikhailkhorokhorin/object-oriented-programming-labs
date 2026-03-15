#include "bear.hpp"

#include "gtest/gtest.h"
#include "rogue.hpp"
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

TEST(BearTest, ConstructorAndGetType) {
    Point point(10, 20);
    Bear bear("Baloo", point);
    EXPECT_EQ(bear.getName(), "Baloo");
    EXPECT_EQ(bear.getType(), "Bear");
    EXPECT_EQ(bear.getPosition().getX(), 10);
    EXPECT_EQ(bear.getPosition().getY(), 20);
}

TEST(BearTest, KillsLogic) {
    Point point1(0, 0);
    Bear bear1("Baloo", point1);

    Point point2(1, 1);
    Werewolf werewolf1("Lupin", point2);
    Rogue rogue1("Robin", point2);

    EXPECT_TRUE(bear1.kills(werewolf1));
    EXPECT_FALSE(bear1.kills(rogue1));
    EXPECT_FALSE(bear1.kills(bear1));
}

TEST(BearTest, AcceptVisitor) {
    Point point1(0, 0);
    Bear bear1("Baloo", point1);

    Point point2(1, 1);
    Werewolf werewolf1("Lupin", point2);

    DummyVisitor visitor1;
    bear1.accept(visitor1, werewolf1);

    EXPECT_TRUE(visitor1.visitedBear);
    EXPECT_FALSE(visitor1.visitedRogue);
    EXPECT_FALSE(visitor1.visitedWerewolf);
}
