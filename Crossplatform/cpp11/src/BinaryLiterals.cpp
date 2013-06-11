#include <++cpp11.h>

// Binary literals

void BinaryLiterals() {
    unsigned int b = 0b11110000;
    outHeader("Binary literals");
    outIdent();
    std::cout
        << "b = "
        << b;
    outTail();
}
