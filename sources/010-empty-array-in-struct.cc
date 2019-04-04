// c/c++ support the empty array definition in structure, this is useful when
// want to description the structure which own fixed-length header and variable-
// length payload

// As blow:

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <iostream>

struct String {
    size_t cap;
    size_t len;
    char buf[0];
};

// We can see the buf[0] don't consumpt memory in fact
static_assert(sizeof(String) == 2 * sizeof(size_t), "Expect sizeof assert!");

int main(int argc, char* argv[]) {
    std::clog << std::endl << std::endl;
    std::clog << "010 empty array in struct" << std::endl;

    //                       header    + real string
    String* s = reinterpret_cast<String*>(malloc(sizeof(String) + 32));
    s->cap = 32;
    s->len = 0;

    strcpy(s->buf, "Hello World!");
    s->len = sizeof("Hello World!");

    printf("%s", s->buf);

    return 0;
}

// Now, Why not pointer?
// struct {
//     size_t cap;
//     size_t len;
//     char * buf;
// }

// Tow resons:
// 1. One more pointer memory consumption
// 2. Better Locality in one whole memory block instead of two seprated blocks.
