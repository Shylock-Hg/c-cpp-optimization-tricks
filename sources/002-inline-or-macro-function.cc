#include <cassert>

#include <iostream>
#include <stdexcept>

// The *inline* keyword is added to standard from C99

// Key Conception:
// 1. Syntax Inline: specify *inline* keyword without syntax error.
// 2. Sementic Inline: the compiler actually generate the inline statements.

// In fact, this keyword suggest compiler to optimize function call to
// inline statements.And this can avoid the multi-defined error in link time.

// Syntax Inline is a syntax mark in source to suggest compiler.

// Sementic Inline is a compile-time operation and require the compiler
// can determine the all information about inline function and its arguments,
// and Sementic Inline will not works when requirements is not statisfied.

inline int iadd(int a, int b) { return a + b; }

// \WARN Modern compiler will consider to inline code even
//       without *inline* keyword when the function is time-consumption-less.
int add(int a, int b) { return a + b; }

// Apply *inline* to recursive function is UB(undefined behavior)
// For modern compiler,some apply Sementic Inline to several deepth,
// and the others choose to ignore it.
// But for stupied compilers,it maybe generate code infinitely.
inline int fib(int n) {
    if (n < 0) {
        throw std::invalid_argument("Invalid negtive fibnacci number!");
    }
    if (0 == n) {
        return 0;
    }
    if (1 == n) {
        return 1;
    }

    return fib(n - 1) + fib(n - 2);
}

// Virtual Function: Possible to Sementic Inline when compiler know the actual
// type of object(In fact know function) and arguments.
class test {
   public:
    inline test(){};
    inline ~test(){};
    inline virtual void hello() { std::clog << "Hello World!" << std::endl; }
};
// In fact, the functions defined in header in c++ are automatic Syntax Inline
// for avoiding link-time multi-defined error.

// The macro function is the sources character replacing
// Compare to inline function, it lack:
//     1. Typed Parameter
//     2. Lexical Scope Isolation
//     3. Return Statement (WARNING)
// The power of macro function is can be embeded to current context without
// Lexical Scope Isolation.
#define madd(a, b) ((a) + (b))

int main(int argc, char* argv[]) {
    std::clog << std::endl << std::endl;
    std::clog << "002-inline-or-macro-function" << std::endl;

    // in fact, std::clog << 2 + 3 << std::endl;
    // without function calling.
    assert(5 == iadd(2, 3));
    // std::clog << iadd(2, 3) << std::endl;

    // Call function if without inline
    assert(5 == add(2, 3));
    // std::clog << add(2, 3) << std::endl;

    // Replace to (2 + 3) in fact.
    assert(5 == madd(2, 3));
    // std::clog << madd(2, 3) << std::endl;

    // Nice guy make it works well.
    assert(3 == fib(4));
    // std::clog << fib(4) << std::endl;

    return 0;
}
