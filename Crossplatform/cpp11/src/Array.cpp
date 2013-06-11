#include <array> // for std::array

#include <++cpp11.h>

// std::array

void Array() {
    std::array<int, 10> a;
    for (auto& i : a) i = 42;
    for (auto i = a.begin(); i != a.end(); ++i) *i = 24;
    int size = a.size();
    outHeader("std::array");
    outIdent();
    std::cout
        << "size = "
        << size;
    outTail();
}
