#include <forward_list> // for std::forward_list

#include <++cpp11.h>

// std::forward_list

void ForwardList() {
    std::forward_list<int> fl;
    for (int i = 0; i < 10; ++i) fl.push_front(i);
    outHeader("std::forward_list");
    outIdent();
    for (const auto& i : fl) std::cout << i;
    std::cout << std::endl;
    // no size()
    // no reverse iteration
    // no back() or push_back()
}
