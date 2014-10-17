#include <++c.h>

// alignment

void Alignment() {
    struct alignas(double) S {
        int a;
        int b;
    };
    constexpr int n = alignof(int);
    outHeader("alignment");
    outIdent();
    std::cout
        << "alignof(int) = "
        << n;
    outTail();
}
