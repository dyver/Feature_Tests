#include <cstdint>

template<typename U, typename T> U any_cast(T t) {
    uint64_t i = (uint64_t)t;
    return (U)i;
}

void f() {
}

using PF = void (*)();

int main() {
    PF pf = f;
    uint64_t i = (uint64_t)pf;
    void* p = (void*)i;

    PF pf3 = any_cast<PF>(p);
    pf3();

    return 0;
}
