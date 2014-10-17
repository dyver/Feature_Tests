#include <++c.h>

#include <algorithm> // for std::sort

// algorithms improvements

void AlgorithmsImprovements() {
    outHeader("algorithms improvements");
    outIdent();
    // effects of move
    std::vector<int> v = { 3, 2, 1 };
    std::sort(v.begin(), v.end());
    std::cout
        << "effects of move : sorted vector = ";
    for (auto const& i : v) std::cout << i << " ";
    outTail();
    // use of lambdas
    auto lambda = [](int a, int b) { return a < b; };
    bool sorted = std::is_sorted(v.begin(), v.end(), lambda);
    outIdent();
    std::cout
        << "use of lambdas : is vector sorted = "
        << sorted;
    outTail();
    // use of initializer lists
    int min = std::min({1, 2, 3});
    outIdent();
    std::cout
        << "use of initializer lists : min of array = "
        << min;
    outTail();
}
