#include <++c.h>

// Binary literals

void BinaryLiterals() {
    unsigned int b = 0b11110000;
    outHeader("Binary literals");
    outIdent();
    std::cout
        << "0b11110000 = "
        << b;
    outTail();
}
