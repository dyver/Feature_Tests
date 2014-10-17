#include <++c.h>

// range-for statement

void RangeForStatement() {
    std::vector<double> vec;
    vec.resize(10);
    // changing values
    for (auto& i : vec) {
        i = 42.42;
    }
    // changing only local copies
    for (auto i : vec) {
        i = i + 1.1;
    }
    // giving const references
    for (const auto& i : vec) {
        // i = i + 1.1; // forbidden
        vec[0] = i;
    }
}
