#include <++cpp11.h>

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
    clock_t before, after;
    double difference;
    before = clock();
    {
        // returning container without copy
        std::vector<int> mv = moveOperatorsFunction(vec_size);
    }
    after = clock();
    difference = double(after - before) / CLOCKS_PER_SEC;
    outIdent();
    std::cout << "Without copy elapsed seconds: " << difference << std::endl;
    before = clock();
    {
        // passing container by reference
        // must be the same efficiency as above
        std::vector<int> mv(vec_size);
        moveOperatorsFunctionToCompare(mv);
    }
    after = clock();
    difference = double(after - before) / CLOCKS_PER_SEC;
    outIdent();
    std::cout << "By reference elapsed seconds: " << difference << std::endl;
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
