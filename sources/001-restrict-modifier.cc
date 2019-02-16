#include <cstddef>

#include <iostream>

// The keyword *restrict* is available from C99,
// not in C++ standard but supported by many compiler but using *__restrict*

// The *restrict* is applied only to pointer to prompt to compiler that this
// pointer is the only way to access this resource in its own lifetime.
// The compiler will to or not to optimize the code generated.

// \WARNING If apply *restrict* to one pointer and there are other way to
//          access the memory it point to in itself lifetime, this is
//          UB(Undefined Behavior).

// In fact, if there are the possiblity which exists multiple way to access the
// memory pointed to, the compiler must generate extra code to load the origin
// data from memory instead of using cache/register. If we can guarantee this
// pointer is the only way to acess the resource and apply *restrict* keyword,
// the compiler could omit the reload operation.

int add(int * a, int * b) {
    *a = 3;
    *b = 4;
    return *a + *b;  //!< Not always 7, can be 8 when a can equals to b
}

int radd(int * __restrict a, int * __restrict b) {
    *a = 3;
    *b = 4;
    return *a + *b;  //!< here we can even evaluate the value in compile-time
}

// \NOTE argument and parameter about `dest` can access the memory
//       itself point to in this process, but in parameter's
//       lifetime (this function scope), it's the only way to access this.
//       (Maybe not OK in multi-threads process)
//       So we can apply *restrict* to the parameter pointer.
void* memcpy(void * __restrict dest, void * __restrict src, std::size_t n) {
    if (NULL == dest || NULL == src || 0 == n) {
        return NULL;
    }
    for (std::size_t i = 0; i < n; i++) {
        ((uint8_t*)dest)[i] = ((uint8_t*)src)[i];
    }
    return dest;
}

int main(int argc, char * argv[]) {
    int a,b;
    std::clog << add(&a, &b) << std::endl;
    std::clog << radd(&a, &b) << std::endl;
    std::clog << add(&a, &a) << std::endl;
    // std::clog << radd(&a, &a) << std::endl;  \WARNING

    char src[] = "Hello World!";
    char dest[sizeof(src)];
    if (NULL != memcpy(dest, src, sizeof(dest))) {
        std::clog << "Dest is `" << dest << "`" << std::endl;
    }

    return 0;
}
