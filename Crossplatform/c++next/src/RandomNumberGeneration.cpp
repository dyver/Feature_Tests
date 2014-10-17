#include <random> // for random number generation
#include <functional> // std::bind

#include <++c.h>

// Random number generation

void RandomNumberGeneration() {
    // uniform distribution
    const int RollDiceTotal = 10;
    std::uniform_int_distribution<int> from_1_to_5{1, 5};
    std::default_random_engine re;
    outHeader("Random number generation");
    outIdent();
    std::cout << "strict call result = ";
    for (auto i = 0; i < RollDiceTotal; ++i) {
        int result = from_1_to_5(re);
        std ::cout << result << " ";
    }
    std::cout << std::endl;
    auto dice(std::bind(from_1_to_5, re));
    outIdent();
    std::cout << "binded call result = ";
    for (auto i = 0; i < RollDiceTotal; ++i) {
        int result = dice();
        std ::cout << result << " ";
    }
    std::cout << std::endl;
    // normal distribution
    std::normal_distribution<float> nd(31, 8);
    auto norm = std::bind(nd, re);
    std::vector<int> mn(64);
    for (auto i = 0; i < 1200; ++i) ++mn[std::round(norm())];
    for (auto i = 0U; i < mn.size(); ++i) {
        std::cout << i << '\t';
        for (int j = 0; j < mn[i]; ++j) std::cout << '*';
        std::cout << '\n';
    }
}
