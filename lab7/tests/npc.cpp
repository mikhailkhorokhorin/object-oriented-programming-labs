#include "npc.hpp"

#include <gtest/gtest.h>

#include "point.hpp"

class MockNPC : public NPC {
   public:
    MockNPC(const std::string& name, const Point& pos) : NPC(name, pos) {
    }

    std::string getType() const override {
        return "Mock";
    }

    int getMoveDistance() const override {
        return 0;
    }

    int getKillDistance() const override {
        return 0;
    }

    bool kills(const NPC& other) const override {
        return false;
    }
};

TEST(NPCTest, ConstructorAndName) {
    MockNPC npc("TestNPC", Point(10, 20));
    EXPECT_EQ(npc.getName(), "TestNPC");
}

TEST(NPCTest, PositionAccessAndMove) {
    MockNPC npc("TestNPC", Point(10, 20));
    Point pos = npc.getPosition();
    EXPECT_EQ(pos.getX(), 10);
    EXPECT_EQ(pos.getY(), 20);

    npc.move(5, -5, 100, 100);
    pos = npc.getPosition();
    EXPECT_EQ(pos.getX(), 15);
    EXPECT_EQ(pos.getY(), 15);

    npc.move(-50, 200, 100, 100);
    pos = npc.getPosition();
    EXPECT_EQ(pos.getX(), 0);
    EXPECT_EQ(pos.getY(), 100);
}

TEST(NPCTest, AliveKill) {
    MockNPC npc("TestNPC", Point(0, 0));
    EXPECT_TRUE(npc.isAlive());
    npc.kill();
    EXPECT_FALSE(npc.isAlive());
}

TEST(NPCTest, DistanceTo) {
    MockNPC npc1("A", Point(0, 0));
    MockNPC npc2("B", Point(3, 4));
    EXPECT_DOUBLE_EQ(npc1.distanceTo(npc2), 5.0);
}

TEST(NPCTest, DeadDoesNotMove) {
    MockNPC npc("TestNPC", Point(10, 10));
    npc.kill();
    npc.move(10, 10, 100, 100);
    Point pos = npc.getPosition();
    EXPECT_EQ(pos.getX(), 10);
    EXPECT_EQ(pos.getY(), 10);
}
