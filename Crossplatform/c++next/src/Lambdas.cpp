#include <algorithm> // for std::for_each

#include <++c.h>

// lambdas

void Lambdas() {
    std::vector<int> someList = { 1, 2, 3 };
    int total = 0;
    std::for_each(someList.begin(), someList.end(), [&total](int x) {
        total += x;
    });
    auto lambda = [&total](int x) { return x + 10; };
    std::for_each(someList.begin(), someList.end(), lambda);
    auto lambda2 = [] { return 10; };
    auto res = lambda2();
    // specifying return value cause it can't be dedused
    auto lambda3 = []() -> int { int i = 0; return i + 1; };
    res = lambda3();
    res++;
}
