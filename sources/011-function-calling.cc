// The difference between literal function calling and function pointer calling

// See detail in https://godbolt.org/z/q5MG85ode

// As above, the function pointer calling have a extra instruction that push the function pointer
// value to the register, the call by the value of this register

int add(int a, int b) {
    return a + b;
}

int main () {
    int(*a)(int, int) = add;
    add(1, 2);
    a(1, 2);
    return 0;
}
