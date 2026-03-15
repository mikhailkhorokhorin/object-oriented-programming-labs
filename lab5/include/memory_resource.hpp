#pragma once

#include <cstddef>
#include <map>
#include <memory_resource>
#include <new>
#include <vector>

class MemoryResource : public std::pmr::memory_resource {
   private:
    std::map<void*, size_t> allocatedBlocks_;
    std::map<size_t, std::vector<void*>> freeBlocks_;

   protected:
    void* do_allocate(size_t bytes, size_t alignment) override {
        auto it = freeBlocks_.lower_bound(bytes);
        if (it != freeBlocks_.end() && !it->second.empty()) {
            void* ptr = it->second.back();
            it->second.pop_back();
            allocatedBlocks_[ptr] = bytes;
            return ptr;
        }

        void* ptr = ::operator new(bytes, std::align_val_t(alignment));
        allocatedBlocks_[ptr] = bytes;
        return ptr;
    }

    void do_deallocate(void* p, size_t bytes, size_t alignment) override {
        auto it = allocatedBlocks_.find(p);
        if (it != allocatedBlocks_.end()) {
            allocatedBlocks_.erase(it);
            freeBlocks_[bytes].push_back(p);
        }
    }

    bool do_is_equal(const memory_resource& other) const noexcept override {
        return this == &other;
    }

   public:
    ~MemoryResource() {
        for (auto& [ptr, size] : allocatedBlocks_)
            ::operator delete(ptr, std::align_val_t(alignof(std::max_align_t)));
        for (auto& [size, vec] : freeBlocks_)
            for (void* ptr : vec)
                ::operator delete(ptr, std::align_val_t(alignof(std::max_align_t)));
    }
};
