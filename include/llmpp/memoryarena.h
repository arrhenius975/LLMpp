#pragma once

#include <cstddef>
#include <vector>
#include <memory>

namespace llmpp {

class MemoryArena {
public:
    explicit MemoryArena(size_t block_size = 1024 * 1024);
    ~MemoryArena() = default;

    MemoryArena(const MemoryArena&) = delete;
    MemoryArena& operator=(const MemoryArena&) = delete;

    void* allocate(size_t size, size_t alignment = alignof(std::max_align_t));
    void reset();

private:
    size_t block_size_;
    std::vector<std::unique_ptr<char[]>> blocks_;
    char* current_block_;
    size_t used_;
};

} // namespace llmpp