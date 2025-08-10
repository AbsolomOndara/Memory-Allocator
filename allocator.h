#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <cstddef> // for size_t

class MemoryAllocator {
public:
    MemoryAllocator();
    ~MemoryAllocator();

    void* allocate(size_t size);
    void deallocate(void* ptr);

    // Disable copy and assignment
    MemoryAllocator(const MemoryAllocator&) = delete;
    MemoryAllocator& operator=(const MemoryAllocator&) = delete;

private:
    struct Block {
        size_t size;
        bool used;
        Block* next;
        void* data;
    };

    Block* head;
    Block* tail;
    void* memoryPool;
    const size_t POOL_SIZE = 1024 * 1024; // 1MB pool

    Block* findFreeBlock(size_t size);
    void splitBlock(Block* block, size_t size);
    void mergeFreeBlocks();
};

// C-style interface
extern "C" {
    void* my_malloc(size_t size);
    void my_free(void* ptr);
}

#endif // ALLOCATOR_H