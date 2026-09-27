#include "memory_resource.hpp"

#include <gtest/gtest.h>

#include <cstdint>
#include <vector>

namespace {

bool isAligned(const void* ptr, std::size_t alignment) {
    return reinterpret_cast<std::uintptr_t>(ptr) % alignment == 0;
}

}

TEST(MemoryResourceTest, TracksUsedAndFreeBlocks) {
    MemoryResource resource;
    void* first = resource.allocate(64);
    void* second = resource.allocate(128);
    EXPECT_NE(first, second);
    EXPECT_EQ(resource.usedBlockCount(), 2U);
    EXPECT_EQ(resource.freeBlockCount(), 0U);

    resource.deallocate(first, 64);
    EXPECT_EQ(resource.usedBlockCount(), 1U);
    EXPECT_EQ(resource.freeBlockCount(), 1U);

    resource.deallocate(second, 128);
    EXPECT_EQ(resource.usedBlockCount(), 0U);
    EXPECT_EQ(resource.freeBlockCount(), 2U);
}

TEST(MemoryResourceTest, ReusesFreedBlockOfSameSize) {
    MemoryResource resource;
    void* first = resource.allocate(32);
    resource.deallocate(first, 32);
    void* second = resource.allocate(32);
    EXPECT_EQ(first, second);
    EXPECT_EQ(resource.freeBlockCount(), 0U);
    resource.deallocate(second, 32);
}

TEST(MemoryResourceTest, ReusesLargerBlockForSmallerRequest) {
    MemoryResource resource;
    void* large = resource.allocate(256);
    resource.deallocate(large, 256);
    void* small = resource.allocate(16);
    EXPECT_EQ(small, large);
    resource.deallocate(small, 16);
    void* again = resource.allocate(200);
    EXPECT_EQ(again, large);
    resource.deallocate(again, 200);
}

TEST(MemoryResourceTest, DoesNotReuseTooSmallBlock) {
    MemoryResource resource;
    void* small = resource.allocate(16);
    resource.deallocate(small, 16);
    void* large = resource.allocate(64);
    EXPECT_NE(small, large);
    EXPECT_EQ(resource.freeBlockCount(), 1U);
    resource.deallocate(large, 64);
}

TEST(MemoryResourceTest, RespectsRequestedAlignment) {
    constexpr std::size_t BIG_ALIGNMENT = 256;
    MemoryResource resource;
    void* plain = resource.allocate(16, alignof(int));
    resource.deallocate(plain, 16, alignof(int));
    void* aligned = resource.allocate(16, BIG_ALIGNMENT);
    EXPECT_TRUE(isAligned(aligned, BIG_ALIGNMENT));
    resource.deallocate(aligned, 16, BIG_ALIGNMENT);
    void* reused = resource.allocate(8, alignof(int));
    EXPECT_TRUE(isAligned(reused, alignof(int)));
    resource.deallocate(reused, 8, alignof(int));
}

TEST(MemoryResourceTest, ReleasesOverAlignedBlocksOnDestruction) {
    constexpr std::size_t BIG_ALIGNMENT = 128;
    MemoryResource resource;
    void* kept = resource.allocate(64, BIG_ALIGNMENT);
    void* freed = resource.allocate(32, BIG_ALIGNMENT);
    resource.deallocate(freed, 32, BIG_ALIGNMENT);
    EXPECT_TRUE(isAligned(kept, BIG_ALIGNMENT));
    EXPECT_EQ(resource.usedBlockCount(), 1U);
    EXPECT_EQ(resource.freeBlockCount(), 1U);
}

TEST(MemoryResourceTest, IgnoresUnknownPointer) {
    MemoryResource resource;
    int local = 0;
    resource.deallocate(&local, sizeof(local));
    EXPECT_EQ(resource.freeBlockCount(), 0U);
}

TEST(MemoryResourceTest, EqualityIsIdentity) {
    MemoryResource first;
    MemoryResource second;
    EXPECT_TRUE(first.is_equal(first));
    EXPECT_FALSE(first.is_equal(second));
}

TEST(MemoryResourceTest, ManyBlocksAreRecycled) {
    MemoryResource resource;
    std::vector<void*> blocks;
    for (int i = 0; i < 100; ++i) {
        blocks.push_back(resource.allocate(16));
    }
    for (void* block : blocks) {
        resource.deallocate(block, 16);
    }
    for (auto& block : blocks) {
        block = resource.allocate(16);
    }
    EXPECT_EQ(resource.usedBlockCount(), 100U);
    EXPECT_EQ(resource.freeBlockCount(), 0U);
}
