// The Conditional Prediction Optimization also refer to the Principle of
// Locality.
// The compiler generate the code of likely branch to near to function
// entry and generate the code of unlikely branch to far away from function
// entry.

// There are Conditional Branch Prediction feature in two way:

// 0. Compiler Extension:
#define likely(bexpr)   __builtin_expect(!!(bexpr), 1)
#define unlikely(bexpr) __builtin_expect(!!(bexpr), 0)
// In fact, *__builtin_expected* can do more value prediction optimization
// than just condition.
#include <cstdint>
#include <iostream>
void cond_pred(std::uint32_t num) {
    if (likely(num < 10)) {  // more possible in input distribution
        std::clog << "More likely!" << std::endl;
    } else if(unlikely(num > 1024)) {  // less possible in input distribution
        std::clog << "Less likely!" << std::endl;
    } else { // normal possible
         std::clog << "Normal likely!" << std::endl;
    }
}


// 1. c++20 standard but not implemented by compiler now
// Defined as attributes:
void pp_cond_pred(std::uint32_t num) {
    if (num < 10) [[likely]] {
        std::clog << "More likely!" << std::endl;
    } else if (num > 1024) [[unlikely]] {
        std::clog << "Less likely!" << std::endl;
    } else { // normal possible
         std::clog << "Normal likely!" << std::endl;
    }
}

#include <array>

int main(int argc, char * argv[]) {
    std::clog << std::endl << std::endl;
    std::clog << "006 conditional branch prediction" << std::endl;

    // 6 items < 10
    // 1 items > 1024
    // 3 items others
    std::array<std::uint32_t, 10> t = {2, 3, 4, 9, 10, 33, 5, 2222, 233, 3};
    for (const auto & i : t) {
        cond_pred(i);
    }
    for (const auto & i : t) {
        pp_cond_pred(i);
    }
    return 0;
}
