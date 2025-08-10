#include "allocator.h"
#include <cstdlib> // for malloc, free
#include <cstring> // for memset
#include <iostream>

MemoryAllocator::MemoryAllocator() {
    memoryPool = malloc(POOL_SIZE);
    if (!memoryPool) {
        std::cerr << "Failed to allocate memory pool!" << std::endl;
        exit(1);
    }

    // Initialize the first block
    head = reinterpret_cast<Block*>(memoryPool);
    head->size = POOL_SIZE - sizeof(Block);
    head->used = false;
    head->next = nullptr;
    head->data = reinterpret_cast<char*>(memoryPool) + sizeof(Block);

    tail = head;
}

MemoryAllocator::~MemoryAllocator() {
    free(memoryPool);
}

MemoryAllocator::Block* MemoryAllocator::findFreeBlock(size_t size) {
    Block* current = head;
    while (current) {
        if (!current->used && current->size >= size) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void MemoryAllocator::splitBlock(Block* block, size_t size) {
    if (block->size > size + sizeof(Block)) {
        Block* newBlock = reinterpret_cast<Block*>(
            reinterpret_cast<char*>(block) + sizeof(Block) + size);
        
        newBlock->size = block->size - size - sizeof(Block);
        newBlock->used = false;
        newBlock->next = block->next;
        newBlock->data = reinterpret_cast<char*>(newBlock) + sizeof(Block);

        block->size = size;
        block->next = newBlock;

        if (block == tail) {
            tail = newBlock;
        }
    }
}

void MemoryAllocator::mergeFreeBlocks() {
    Block* current = head;
    while (current && current->next) {
        if (!current->used && !current->next->used) {
            current->size += sizeof(Block) + current->next->size;
            current->next = current->next->next;
            
            if (current->next == nullptr) {
                tail = current;
            }
        } else {
            current = current->next;
        }
    }
}

void* MemoryAllocator::allocate(size_t size) {
    if (size == 0) {
        return nullptr;
    }

    // Align size to 8 bytes
    size = (size + 7) & ~7;

    Block* block = findFreeBlock(size);
    if (!block) {
        mergeFreeBlocks();
        block = findFreeBlock(size);
        if (!block) {
            return nullptr; // Out of memory
        }
    }

    if (block->size >= size + sizeof(Block) + 8) {
        splitBlock(block, size);
    }

    block->used = true;
    return block->data;
}

void MemoryAllocator::deallocate(void* ptr) {
    if (!ptr) {
        return;
    }

    Block* block = reinterpret_cast<Block*>(
        reinterpret_cast<char*>(ptr) - sizeof(Block));
    
    block->used = false;
    mergeFreeBlocks();
}

// Global allocator instance
static MemoryAllocator allocator;

// C-style interface implementation
extern "C" {
    void* my_malloc(size_t size) {
        return allocator.allocate(size);
    }

    void my_free(void* ptr) {
        allocator.deallocate(ptr);
    }
}