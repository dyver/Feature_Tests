#include <chrono> // for time utilities

#include <++c.h>

// container improvements

// move operators
std::vector<int> moveOperatorsFunction(int n) {
    std::vector<int> v(n);
    for (auto& i : v) i = 42;
    return v;
}

void moveOperatorsFunctionToCompare(std::vector<int>& v) {
    for (auto& i : v) i = 42;
}

void ContainerImprovements() {
    // initializer lists
    std::vector<std::string> v = { "Hello", ", ", "word", "!" };
    outHeader("container improvements");
    outIdent();
    for (auto& i : v) std::cout << i;
    std::cout << std::endl;
    // move operators
    const int vec_size = 10000000;
    using namespace std::chrono;
    auto before = system_clock::now();
    {
        // returning container without copy
        std::vector<int> mv = moveOperatorsFunction(vec_size);
    }
    microseconds elapsed = duration_cast<microseconds>(system_clock::now() - before);
    outIdent();
    std::cout << "Without copy elapsed seconds: " << elapsed.count() << std::endl;
    before = system_clock::now();
    {
        // passing container by reference
        // must be the same efficiency as above
        std::vector<int> mv(vec_size);
        moveOperatorsFunctionToCompare(mv);
    }
    elapsed = duration_cast<microseconds>(system_clock::now() - before);
    outIdent();
    std::cout << "By reference elapsed seconds: " << elapsed.count() << std::endl;
    // improved push operations
    std::vector<std::pair<int, std::string>> ipv;
    for (int i = 0; i < 10; ++i) {
        ipv.push_back({i, "test"}); // no copy of pair but moving it
    }
    // emplace operations
    std::vector<std::pair<int, std::string>> ev;
    for (int i = 0; i < 10; ++i) {
        ev.emplace_back(i, "test"); // constructing pair "inplace"
    }
}
