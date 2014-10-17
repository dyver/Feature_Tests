#include <++c.h>

// nullptr - a null pointer literal

inline void nullptrTestFunction(int) {
    std::cout
        << "called nullptrTestFunction(int)"
        << std::endl;
}

inline void nullptrTestFunction(char*) {
    std::cout
        << "called nullptrTestFunction(char *)"
        << std::endl;
}

void NullPtr() {
    outHeader("nullptr - a null pointer literal");
    outIdent();
    nullptrTestFunction(nullptr);
    outIdent();
    nullptrTestFunction(0);
}
