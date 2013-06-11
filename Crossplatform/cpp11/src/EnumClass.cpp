#include <++cpp11.h>

// enum class - scoped and strongly typed enums

enum class ClassEnum : char {
    red,
    white,
    blue
};

inline ClassEnum operator++(ClassEnum ce) { // prefix form
    if (ce == ClassEnum::blue) return ClassEnum::red;
    return ClassEnum(int(ce) + 1);
}

inline ClassEnum operator++(ClassEnum ce, int) { // postfix form
    return ++ce;
}

enum class ClassEnum2 {
    red,
    bad,
    fat = 10000
};

inline int operator|(ClassEnum ce, ClassEnum2 ce2) {
    return int(ce) | int(ce2);
}

void EnumClass() {
    ClassEnum ce = ClassEnum::white;
    ClassEnum2 ce2 = ClassEnum2::fat;
    int i = ce | ce2;
    i = ClassEnum::blue | ClassEnum2::bad;
    outHeader("enum class - scoped and strongly typed enums");
    outIdent();
    std::cout
        << "operator |() result: " << i
        << std::endl;
    outIdent();
    std::cout
        << "operator ++(int) result: " << int(ce++)
        << std::endl;
    outIdent();
    std::cout
        << "operator ++() result: " << int(++ce)
        << std::endl;
}
