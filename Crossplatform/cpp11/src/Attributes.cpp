#include <++cpp11.h>

// attributes

[[noreturn]] void functionWithAttribute() {
    throw int();
    // return; // forbidden
}

void Attributes() {
    functionWithAttribute();
}
