#include <++c.h>

// attributes

[[noreturn]] void functionWithAttribute() {
    throw int();
    // return; // forbidden
}

void Attributes() {
    try {
        functionWithAttribute();
    } catch (...) {}
}
