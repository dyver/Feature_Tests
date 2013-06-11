#include <++cpp11.h>

// preventing narrowing

void PreventingNarrowing() {
    // int x0{7.3}; // error: narrowing
    int x1{7}; // ok
    double d = 7;
    // int x2{d}; // error: narrowing (double to int)
    char x3{7}; // ok: even though 7 is an int, this is not narrowing
    x1++; d = d + 1.1; x3++;
}
