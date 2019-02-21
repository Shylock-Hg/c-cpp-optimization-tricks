// The bit operator will be compiled to one origin cpu instruction, so bit
// operator is always effective.

// The available bit operator in c/c++:
// Bit And         - &
// Bit Or          - |
// Bit Not         - ~
// Bit XOR         - ^
// Bit Left Shift  - <<
// Bit Right Shift - >>

// Many expensive operations can be replaced to equivalent bit operatons as
// below:

// 0. Check ODD or EVEN?
template <typename T>
constexpr T
is_odd(T digit) noexcept(noexcept(T(digit))) {
    return 1U & digit;
}
static_assert(true == is_odd(3), "is_odd check error!");
static_assert(false == is_odd(4), "is_odd check error!");
static_assert(false == is_odd(0), "is_odd check error!");
static_assert(true == is_odd(-1), "is_odd check error!");
static_assert(false == is_odd(-4), "is_odd check error!");

// 1. Multiple or Divide 2
// left shift is well for positive(signed or unsigned), UB for negative
template <typename T>
constexpr  T
mult_two(T opnd) noexcept(noexcept(T(opnd))) {
    return opnd << 1U;
}
static_assert(0 == mult_two(0), "mult_two check error!");
// static_assert(-22 == mult_two(-11), "mult_two check error!");
static_assert(44 == mult_two(22), "mult_two check error!");

template <typename T>
constexpr T
divide_two(T opnd) noexcept(noexcept(T(opnd))) {
    return opnd >> 1U;
}
static_assert(0 == divide_two(0), "divide_two check error!");
static_assert(-11 == divide_two(-22), "divide_two check error!");
static_assert(22 == divide_two(44), "divide_two check error!");

// 3. Check all bits zero or one?
static_assert((0 | 0 | 0) == 0, "check all zero error!");
static_assert((false == ((-1 | 0 | 3) == 0)), "check all zero error!");

static_assert((-1 & -1 & -1 ) == -1, "check all one error!");
static_assert(false == ((33 & -1 & -1 ) == -1), "check all one error!");

// and more

#include <iostream>


int main(int argc, char * argv[]) {
    std::clog << std::endl << std::endl;
    std::clog << "007-bit-operator" << std::endl;
    return 0;
}

// reference:
// [0]: https://graphics.stanford.edu/~seander/bithacks.html
