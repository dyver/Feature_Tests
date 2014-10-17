#include <algorithm> // for std::sort

#include <++c.h>

// local types as template arguments

template <typename T> void localTypesFunction(std::vector<T>& v) {
    struct Less {
        bool operator ()(const T& a, const T& b) { return a < b; }
    };
    std::sort(v.begin(), v.end(), Less());
}

void LocalTypes() {
    std::vector<int> v = { 3, 5, 2, 6, 7 };
    localTypesFunction(v);
}
