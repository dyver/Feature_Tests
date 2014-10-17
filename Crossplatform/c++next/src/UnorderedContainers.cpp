#include <unordered_map> // for std::unordered_map

#include <++c.h>

// unordered containers

void UnorderedContainers() {
    std::unordered_map<std::string, int> um =
            { {"1 Vinny", 1}, {"2 Pooh", 2}, {"3 Pyatachok", 2} };
    // result is hashed sort order
    // fast search for very lardge containers
    outHeader("unordered containers");
    outIdent();
    for (auto i : um) std::cout << "{" << i.first << "," << i.second << "}";
    std::cout << std::endl;
}
