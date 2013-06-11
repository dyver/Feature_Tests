#include <functional> // for std::function and std::bind

#include <++cpp11.h>

// std::function and std::bind

inline int functionToBind(int i, double d, char c) {
    return i + int(d) + int(c);
}

void FunctionAndBind() {
    using namespace std::placeholders; // for _1, _2, _3 etc arguments
    auto f1 = std::bind(functionToBind, _1, 42.42, 'c');
    outHeader("std::function and std::bind");
    outIdent();
    std::cout
        << "f1 with binding all arguments except first = "
        << f1(1)
        << std::endl;
    auto f2 = std::bind(functionToBind, _3, _2, _1);
    outIdent();
    std::cout
        << "f2 with reverse arguments order = "
        << f2('a', 24.24, 2)
        << std::endl;
    struct FunctionalObject {
        int operator ()(int i, double d, char c) { return i + int(d) + int(c); }
        float mf(int i) { return i + 1.42; }
    };
    std::function<int (int, double, char)> f3;
    f3 = FunctionalObject();
    outIdent();
    std::cout
        << "f3 functional object = "
        << f3(3, 44.44, 'b')
        << std::endl;
    std::function<float (FunctionalObject*, int)> f4;
    f4 = &FunctionalObject::mf;
    FunctionalObject fo;
    outIdent();
    std::cout
        << "f4 functional object from member function = "
        << f4(&fo, 4)
        << std::endl;
    std::function<int (char)> f5;
    f5 = std::bind(functionToBind, 5, 55.55, _1);
    outIdent();
    std::cout
        << "f5 functional object from binded function = "
        << f5('r')
        << std::endl;
}
