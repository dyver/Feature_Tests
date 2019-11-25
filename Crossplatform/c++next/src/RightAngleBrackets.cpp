#include <++c.h>

// right-angle brackets

template<typename T> class RightAngleBracketsClass {
    public:
        T x;
};

void RightAngleBrackets() {
    RightAngleBracketsClass<RightAngleBracketsClass<int>> rav;
    (void)rav;
}
