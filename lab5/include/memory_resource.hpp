#pragma once

#include <cstddef>
#include <cstdint>
#include <map>
#include <memory_resource>
#include <new>

class MemoryResource : public std::pmr::memory_resource {
public:
    MemoryResource() = default;
    MemoryResource(const MemoryResource&) = delete;
    MemoryResource& operator=(const MemoryResource&) = delete;
    MemoryResource(MemoryResource&&) = delete;
    MemoryResource& operator=(MemoryResource&&) = delete;

    ~MemoryResource() override {
        for (const auto& [ptr, block] : used_) {
            release(ptr, block);
        }
        for (const auto& [size, entry] : free_) {
            release(entry.ptr, Block{size, entry.alignment});
        }
    }

    std::size_t usedBlockCount() const { return used_.size(); }

    std::size_t freeBlockCount() const { return free_.size(); }

protected:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override {
        for (auto it = free_.lower_bound(bytes); it != free_.end(); ++it) {
            const FreeEntry entry = it->second;
            if (entry.alignment >= alignment &&
                reinterpret_cast<std::uintptr_t>(entry.ptr) % alignment == 0) {
                used_.emplace(entry.ptr, Block{it->first, entry.alignment});
                free_.erase(it);
                return entry.ptr;
            }
        }
        void* ptr = ::operator new(bytes, std::align_val_t{alignment});
        used_.emplace(ptr, Block{bytes, alignment});
        return ptr;
    }

    void do_deallocate(void* ptr, std::size_t, std::size_t) override {
        const auto it = used_.find(ptr);
        if (it == used_.end()) {
            return;
        }
        free_.emplace(it->second.size, FreeEntry{ptr, it->second.alignment});
        used_.erase(it);
    }

    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }

private:
    struct Block {
        std::size_t size;
        std::size_t alignment;
    };

    struct FreeEntry {
        void* ptr;
        std::size_t alignment;
    };

    std::map<void*, Block> used_;
    std::multimap<std::size_t, FreeEntry> free_;

    static void release(void* ptr, const Block& block) {
        ::operator delete(ptr, block.size, std::align_val_t{block.alignment});
    }
};
