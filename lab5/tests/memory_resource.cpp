#include "memory_resource.hpp"

#include <gtest/gtest.h>

TEST(MemoryResourceTest, AllocateAndDeallocate) {
    MemoryResource mr;

    void* p1 = mr.allocate(64);
    ASSERT_NE(p1, nullptr);

    void* p2 = mr.allocate(128);
    ASSERT_NE(p2, nullptr);

    mr.deallocate(p1, 64);
    mr.deallocate(p2, 128);
}

TEST(MemoryResourceTest, ReuseFreedMemory) {
    MemoryResource mr;

    void* p1 = mr.allocate(32);
    mr.deallocate(p1, 32);

    void* p2 = mr.allocate(32);
    EXPECT_EQ(p1, p2);

    mr.deallocate(p2, 32);
}

TEST(MemoryResourceTest, AllocateDifferentSizes) {
    MemoryResource mr;

    void* p1 = mr.allocate(16);
    void* p2 = mr.allocate(32);
    void* p3 = mr.allocate(64);

    ASSERT_NE(p1, nullptr);
    ASSERT_NE(p2, nullptr);
    ASSERT_NE(p3, nullptr);

    mr.deallocate(p1, 16);
    mr.deallocate(p2, 32);
    mr.deallocate(p3, 64);
}

TEST(MemoryResourceTest, IsEqual) {
    MemoryResource mr1;
    MemoryResource mr2;

    EXPECT_TRUE(mr1.is_equal(mr1));
    EXPECT_FALSE(mr1.is_equal(mr2));
}

TEST(MemoryResourceTest, LargeNumberOfBlocks) {
    MemoryResource     mr;
    std::vector<void*> blocks;

    for (int i = 0; i < 100; i++) {
        void* p = mr.allocate(16);
        blocks.push_back(p);
    }

    for (auto p : blocks)
        mr.deallocate(p, 16);

    for (int i = 0; i < 100; i++) {
        void* p = mr.allocate(16);
        EXPECT_NE(p, nullptr);
    }
}

TEST(MemoryResourceTest, DestructorCleansUp) {
    void* p1;
    {
        MemoryResource mr;
        p1 = mr.allocate(32);
        mr.deallocate(p1, 32);
    }
    SUCCEED();
}
