#include <tuple> // for std::tuple

#include <++c.h>

// std::tuple

void Tuple() {
    outHeader("std::tuple");
    // explicit types declaration
    std::tuple<int, std::string, double> t3(42, "test", 42.42);
    int i = std::get<0>(t3);
    std::string s = std::get<1>(t3);
    double d = std::get<2>(t3);
    outIdent();
    std::cout << "first=" << i << " second=" << s << " third=" << d << std::endl;
    // auto types declaration
    auto t2 = std::make_tuple("test", 42);
    auto tt2 = std::make_tuple("test2", 55);
    outIdent();
    std::cout << "comparing tuples : ";
    if (t2 == tt2) std::cout << "the same tuples";
    else std::cout << "different tuples";
    std::cout << std::endl;
}
