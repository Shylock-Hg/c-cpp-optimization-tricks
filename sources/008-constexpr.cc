// The *constexpr* key word mean evaluate the value of expression at compile
// time if possible.So this also means *syntax* or *semantic*.

static constexpr int i = 1 + 2 + 3;

constexpr int add(int a, int b) {
    // only one return statement in c++11,
    // no this limitation from c++14
    return a + b;
}

#include <iostream>

int main(int argc, char* argv[]) {
    std::clog << std::endl << std::endl;
    std::clog << "008 constexpr" << std::endl;

    int a = add(2, 3);  //!< evaluate on compile time

    return 0;
}
