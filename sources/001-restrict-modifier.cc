#include <iostream>
#include <type_traits>

// The keyword *restrict* is available from C99,
// not in C++ standard but supported by many compiler but using *__restrict*

std::size_t memcpy(void * __restrict dest, void * __restrict src, std::size_t n);

int main(int argc, char * argv[]) {
    return 0;
}
