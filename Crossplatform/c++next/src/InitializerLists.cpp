#include <++c.h>

// initializer lists

inline int intializerListArgumentFunction(std::initializer_list<int> list) {
    int res = 0;
    for (auto i : list) res += i;
    return res;
}

void InitializerLists() {
    std::vector<int> vec = { 1, 2, 3 };
    int i = intializerListArgumentFunction({ 1, 2, 3 });
    i++;
}
