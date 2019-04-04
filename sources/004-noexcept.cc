// The *noexcept* modifier and operator is available from c++11.

// modifier: void func() noexcept;
// Specify the function will not throw exception, if it done std::terminate()
// will be called.
// Compiler can optimize the specified function by avoid generate code for
// stack unwinding.
// Often used in *move constructor/assignment*, *destructor*, *simple function*
// etc.

// operator: bool operator noexcept(expr);
// This return true the expr never throw exception, return false when possibly.
// So can use static_assert/assert to check it.

#include <cassert>

#include <iostream>

int add(int a, int b) noexcept { return a + b; }
static_assert(true == noexcept(add(1, 2)), "Except assert failed!");

//!< determine when specified template
template <typename T>
T tadd(T a, T b) noexcept(noexcept(T(a))) {
    return a + b;
}
// here true
static_assert(true == noexcept(tadd(1, 2)), "Except assert failed!");

class test {
   private:
    std::size_t i_;

   public:
    static void except() { throw "Hello!"; }

    void inc() noexcept { i_++; }
};
static_assert(false == noexcept(test::except()), "Except assert failed!");

#include <string>

int main(int argc, char* argv[]) {
    std::clog << std::endl << std::endl;
    std::clog << "004-noexcept" << std::endl;

    test t;
    assert(true == noexcept(t.inc()));

    std::string s1;
    std::string s2;
    assert(false == noexcept(tadd(s1, s2)));  //!< here false
    return 0;
}

// reference
// [0]. https://isocpp.org/blog/2014/09/noexcept-optimization
