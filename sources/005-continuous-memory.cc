// Refer to Principle of Locality, in modern computer system, the computer
// system is built by many components from cpu to peripheral to network.
// There are always cache between two components which one faster the other
// slower(Such as cpu cache to memory).So if our program access memory or
// fetch instructions in a fixed area in a period of time, the memory
// accessing or instruction fetching will be faster.

// But this always reduce the flexibility of programming.

// Continuous memory strcuture
struct Person
{
    char name[16];
    int age;
};
static_assert(20 == sizeof(Person), "size assert error!");

// Uncontinous memory structure
struct uPerson
{
    // The name string stored in another area (often in heap)
    // So when cpu access name string maybe need to access from memory instead
    // of cache for cache missing.
    // And this will consume more one pointer memory.
    char * name;
    int age;
};
static_assert(16 == sizeof(uPerson), "size assert error!");


#include <iostream>

int main(int argc, char * argv[]) {
    std::clog << std::endl << std::endl;
    std::clog << "005 continuous memory" << std::endl;
    return 0;
}

// Appendx
// The *inline* function introduced before also reflect the Principle of
// Locality in instructions fetcing.
