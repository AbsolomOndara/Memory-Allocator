# Custom Memory Allocator in C++

A custom implementation of `malloc()` and `free()` memory management functions in C++, with benchmarking against the system allocator.

## Features

- Custom memory pool allocator implementation
- Block splitting and coalescing for efficient memory management
- Benchmarking against system `malloc/free`
- First-fit allocation strategy
- Memory usage tracking

## Prerequisites

- C++17 compatible compiler (g++, clang++, or MSVC)
- CMake (optional, for build system)

## Installation & Building

### Using CMake (Recommended)

```bash
mkdir build
cd build
cmake ..
cmake --build .
Manual Compilation
Linux/macOS/WSL (g++/clang++)
bash
g++ -std=c++17 -O3 allocator.cpp main.cpp -o memory_allocator
Windows (MSVC)
cmd
cl /EHsc /std:c++17 allocator.cpp main.cpp /Fe:memory_allocator.exe
Usage
Run the compiled program:

bash
./memory_allocator  # Linux/macOS/WSL
memory_allocator.exe  # Windows
The program will output benchmark results comparing the performance of:

System malloc/free

Custom allocator implementation

Implementation Details
Memory Allocation Strategy
Memory Pool: Pre-allocates 1MB pool at startup

Block Metadata: Tracks size, usage status, and next block

First-fit Allocation: Finds first available block that fits

Block Splitting: Divides large blocks to minimize waste

Coalescing: Merges adjacent free blocks during deallocation

Benchmarking
Tests with 10,000 random allocations (1B-1KB)

Measures total allocation/deallocation time

Compares custom vs system allocator performance

Results Example
Typical output:

text
System malloc/free benchmark: 1582 microseconds
Custom my_malloc/my_free benchmark: 743 microseconds
The custom allocator is typically faster as it:

Avoids repeated system calls after initial pool allocation

Has simpler allocation logic than general-purpose malloc

Benefits from spatial locality within the memory pool

Future Improvements
Implement more allocation strategies (best-fit, worst-fit)

Add thread safety

Support for realloc functionality

More comprehensive benchmarking suite

Memory leak detection

Contributing
Fork the repository

Create your feature branch (git checkout -b feature/fooBar)

Commit your changes (git commit -am 'Add some fooBar')

Push to the branch (git push origin feature/fooBar)

Create a new Pull Request

License
MIT License - see LICENSE file for details

text

### Key Features of this README:

1. **Clear Structure**: Separates installation, usage, and technical details
2. **Multiple Build Options**: Covers CMake, g++, and MSVC
3. **Implementation Explanation**: Helps reviewers understand your design choices
4. **Benchmark Context**: Shows what to expect from the program
5. **Contribution Guidelines**: Makes it easy for others to contribute
6. **Professional Formatting**: Uses proper markdown for GitHub rendering

You can copy this directly into a `README.md` file in your project root directory. The formatting will render properly on GitHub.

Would you like me to add any additional sections, such as:
- More detailed performance analysis?
- Diagrams of the memory layout?
- Specific compiler version requirements?
- Additional benchmark scenarios?
