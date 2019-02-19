// The *noexcept* modifier and operator is available from c++11.

// modifier: void func() noexcept;
// Specify the function will not throw exception, if it done std::terminate()
// will be called.
// Compiler can optimize the specified function by 
// Often used in *move constructor/assignment*, *destructor*, *simple function*
// etc.

// operator: bool operator noexcept(expr);
// This return true the expr never throw exception, return false when possibly.
// So can use static_assert/assert to check it.

#include <cassert>

#include <iostream>

int add(int a, int b) noexcept {
    return a + b;
}
static_assert(true == noexcept(add(1, 2)), "Except assert failed!");

template <typename T>
T tadd(T a, T b) noexcept(noexcept(T(a))) {
    return a + b;
}
static_assert(true == noexcept(tadd(1, 2)), "Except assert failed!");

class test {
private:
    int i;
public:
    static void hello() {
        std::clog << "Hello World!" << std::endl;
    }

    void func() noexcept {
        i++;
    }
};
static_assert(false == noexcept(test::hello()), "Except assert failed!");

#include <string>

int main(int argc, char * argv[]) {
    test t;
    assert(true == noexcept(t.func()));

    std::string s1;
    std::string s2;
    assert(false == noexcept(tadd(s1, s2)));
    return 0;
}
