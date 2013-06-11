#include <++cpp11.h>

// nullptr - a null pointer literal

inline void nullptrTestFunction(int) {
    std::cout << std::endl
        << "nullptr - a null pointer literal"
        << std::endl;
    std::cout << "   "
        << "called nullptrTestFunction(int)"
        << std::endl;
}

inline void nullptrTestFunction(char*) {
    std::cout << std::endl
        << "nullptr - a null pointer literal"
        << std::endl;
    std::cout << "   "
        << "called nullptrTestFunction(char *)"
        << std::endl;
}

void NullPtr() {
    char* ptr1 = nullptr;
    char* ptr2 = 0;
    if (ptr1 == ptr2) {}
    nullptrTestFunction(nullptr);
    nullptrTestFunction(0);
}
