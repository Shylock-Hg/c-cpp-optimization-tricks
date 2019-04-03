#include <cassert>
#include <cstdint>

#include <iostream>

// C/C++ compilers support tail-recursive function optimization when specify
// optimiazation flag `-foptimize-sibling-calls` or
// optimization level from `O2`.

// Using *jump* instead of *call*.

std::uint32_t fib(std::uint32_t n) {
    if (0 == n) {
        return 0;
    }
    if (1 == n) {
        return 1;
    }
    // gcc call this sibling call
    // can optimize fib(n - 2)
    return fib(n - 1) + fib(n - 2);
}

std::uint32_t ofib(std::uint32_t n, std::uint32_t a = 0, std::uint32_t b = 1) {
    if (0 == n) {
        return a;
    }
    if (1 == n) {
        return b;
    }
    return ofib(n - 1, b, a + b);  //!< can optimize fib(n - 1, b, a + b)
}

int main(int argc, char* argv[]) {
    std::clog << std::endl << std::endl;
    std::clog << "003-tail-recursion-optimization" << std::endl;

    assert(3 == fib(4));
    assert(3 == ofib(4));
    return 0;
}
