#include <++c.h>

// auto - deduction of a type from an initializer
// and suffix return type syntax
// and decltype - the type of an expression

template<class U, class V> auto AutoTypeDeductionTemplate(const U u, const V v) -> decltype(u + v) {
    return u + v;
}

void AutoTypeDeduction() {
    auto result = AutoTypeDeductionTemplate(42, 42.42);
    std::vector<int> vec;
    vec.resize(10);
    for (auto i = vec.begin(); i != vec.end(); ++i) {
        *i = 42;
    }
    outHeader("auto - deduction of a type from an initializer");
    outIdent();
    std::cout
        << "result = "
        << result;
    outTail();
}
