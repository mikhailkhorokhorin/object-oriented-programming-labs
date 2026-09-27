#include "npc.hpp"

#include <gtest/gtest.h>

#include "bear.hpp"
#include "rogue.hpp"
#include "visitor.hpp"
#include "werewolf.hpp"

namespace {

class RecordingVisitor final : public Visitor {
public:
    std::string visited;

    void visit(Bear& npc) override { visited = "Bear:" + npc.getName(); }
    void visit(Rogue& npc) override { visited = "Rogue:" + npc.getName(); }
    void visit(Werewolf& npc) override { visited = "Werewolf:" + npc.getName(); }
};

}

TEST(NPCTest, StoresNameTypeAndPosition) {
    const Bear bear("Baloo", Point(10, 20));
    const Rogue rogue("Robin", Point(1, 2));
    const Werewolf werewolf("Lupin", Point(3, 4));
    EXPECT_EQ(bear.getName(), "Baloo");
    EXPECT_EQ(bear.getType(), "Bear");
    EXPECT_EQ(bear.getPosition(), Point(10, 20));
    EXPECT_EQ(rogue.getType(), "Rogue");
    EXPECT_EQ(werewolf.getType(), "Werewolf");
}

TEST(NPCTest, DistanceBetweenNPCs) {
    const Bear bear("Baloo", Point(0, 0));
    const Rogue rogue("Robin", Point(3, 4));
    EXPECT_DOUBLE_EQ(bear.distanceTo(rogue), 5.0);
    EXPECT_DOUBLE_EQ(rogue.distanceTo(bear), 5.0);
}

TEST(NPCTest, AcceptDispatchesOnDynamicType) {
    Bear bear("Baloo", Point());
    Rogue rogue("Robin", Point());
    Werewolf werewolf("Lupin", Point());
    RecordingVisitor visitor;
    NPC* npcs[] = {&bear, &rogue, &werewolf};
    const char* expected[] = {"Bear:Baloo", "Rogue:Robin", "Werewolf:Lupin"};
    for (int i = 0; i < 3; ++i) {
        npcs[i]->accept(visitor);
        EXPECT_EQ(visitor.visited, expected[i]);
    }
}
