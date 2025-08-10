#include "allocator.h"
#include <iostream>
#include <chrono>
#include <vector>
#include <random>

// Benchmark function
template<typename AllocFunc, typename FreeFunc>
void benchmark(const std::string& name, AllocFunc alloc, FreeFunc dealloc, 
               size_t num_allocs, size_t max_size) {
    std::vector<void*> allocations(num_allocs);
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<size_t> size_dist(1, max_size);

    auto start = std::chrono::high_resolution_clock::now();

    // Allocation phase
    for (size_t i = 0; i < num_allocs; ++i) {
        size_t size = size_dist(rng);
        allocations[i] = alloc(size);
    }

    // Deallocation phase
    for (size_t i = 0; i < num_allocs; ++i) {
        dealloc(allocations[i]);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << name << " benchmark: " << duration << " microseconds\n";
}

int main() {
    const size_t NUM_ALLOCS = 10000;
    const size_t MAX_SIZE = 1024; // 1KB

    // Benchmark system allocator
    benchmark("System malloc/free", 
        [](size_t size) { return malloc(size); },
        [](void* ptr) { free(ptr); },
        NUM_ALLOCS, MAX_SIZE);

    // Benchmark custom allocator
    benchmark("Custom my_malloc/my_free", 
        [](size_t size) { return my_malloc(size); },
        [](void* ptr) { my_free(ptr); },
        NUM_ALLOCS, MAX_SIZE);

    return 0;
}