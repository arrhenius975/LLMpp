#include "memoryarena.h"
#include <cstdlib>
#include <cstring>
#include <algorithm>

namespace llmpp {

MemoryArena::MemoryArena(size_t block_size) : block_size_(block_size), current_block_(nullptr), used_(0) {}

void* MemoryArena::allocate(size_t size, size_t alignment) {
    size_t aligned_used = (used_ + alignment - 1) & ~(alignment - 1);
    if (aligned_used + size > block_size_) {
        if (current_block_) {
            blocks_.emplace_back(current_block_);
        }
        current_block_ = new char[block_size_];
        used_ = 0;
        aligned_used = 0;
    }
    void* ptr = current_block_ + aligned_used;
    used_ = aligned_used + size;
    return ptr;
}

void MemoryArena::reset() {
    blocks_.clear();
    delete[] current_block_;
    current_block_ = nullptr;
    used_ = 0;
}

} // namespace llmpp