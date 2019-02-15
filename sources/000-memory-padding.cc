#include <iostream>

class optimized_class {
    int j;
    char i;
    short k;
};

class unoptimized_class {
    char i;
    int j;
    short k;
};

class nested_class {
    optimized_class c;
    char i;
};

///////////////////////////////////////////////////////////////////////////////

struct optimized_struct {
    int j;  // 4B; total 4B here
    char i; // (1 - (4 % 1) % 1) == 0; so 0B padded before; total 1B here
    short k;  // 5 % 2 == 1; so 1B padded before; total 3B here 
    /* padded 0B */  // ((4 - (8 % 4)) % 4 == 0)B; so 0B padded here; total 0B here
    /* So 4 + 1 + 3 == 8B in all */
};

struct unoptimized_struct {
    char i;  // 1B ; total 1B here
    int j;  // (4 - (1 % 4) % 4 == 3; so 3B padded before; total 7B here
    short k;  // (2 - (8 % 2) % 2) == 0; so 0B padded before; total 2B here
    /* padded 2B */  // (4 - (10 % 4)) % 4 == 2; so 2B padded here; total 2B here
    /* So 1 + 7 + 2 + 2 == 12B in all */
    // char h[2];
    // char s;
};

struct nested_struct {
    optimized_struct c;  // 8B; total 8B here
    char i; // (1 - (8 % 1)) % 1 == 0; so 0B padded before; total 1B here
    optimized_struct d;  // (4 - (9 % 4)) % 4 == 3; so 3B padded before; total 11B here
    /* padded 0B */  // (4 - (20 % 4)) % 4 == 0; so 0B padded here; total 0B here
    /* So 8 + 1 + 11 == 20B in all */
    // char j;
};


/* Some basic definition */
// int a;  // item
// struct demo b;  // item
// char c;   // item

// \NOTE this is recursive definition
// If *item* is CPU-Level basic data type (such as *byte*, *half word* and *word*,
// its *alignment size* is same to item's size;
// If *item* is compound type(such as *struct*, *class* and *union* but *array*),
// its *alignment size* is same to the bigest *alignment size* among in members.

/* Two constraints */
// Address Alignment: item must start from address which can be divisible by
// its *alignment size* and padded before when in continuous block to fit if not;
//     The size padded before is calculated by formula as below:
//     padded = (self_align_size - (last_end_offset % self_align_size)) % self_align_size;
//         where last_end_offset is last item ending address offset,
//         self_align_size is the *alignment size* of item calculated now

// Compound Type Size: Total size of compound type (such as *struct*, *class* and *union*)
// must can be divisible by its *alignment size* and padded after to fit if not;
//     The size padded after is calculated by formula as below:
//     padded = (self_align_size - (total_size_naive % self_align_size)) % self_align_size;
//         where total_size_naive is the size of compound type without tail padding,
//         self_align_size is the *alignment size * of the compound type.


// Follow the rules as above.We can optimize the consumption of memory in c/c++ program.
// And the can be applied to function stack, struct inner and class inner etc.
// In all every where the memory pad various-size items continuously.

int main(int argc, char * argv[]) {
    /*
    std::clog << "Size of unoptimized_class is " << sizeof(unoptimized_class);
    std::clog << std::endl << "Size of optimized_class is " << sizeof(optimized_class) << std::endl;
    std::clog << "Size of nested_class is " << sizeof(nested_class) << std::endl;

    std::clog << std::endl;

    std::clog << "Size of unoptimized_struct is " << sizeof(unoptimized_struct) << std::endl;
    std::clog << "Size of optimized_struct is " << sizeof(optimized_struct) << std::endl;
    std::clog << "Size of nested_struct is " << sizeof(nested_struct) << std::endl;
    */
    static_assert(sizeof(unoptimized_class) == 12);
    static_assert(sizeof(optimized_class) == 8);
    static_assert(sizeof(nested_class) == 12);

    static_assert(sizeof(unoptimized_struct) == 12);
    static_assert(sizeof(optimized_struct) == 8);
    static_assert(sizeof(nested_struct) == 20);
    return 0;
}
