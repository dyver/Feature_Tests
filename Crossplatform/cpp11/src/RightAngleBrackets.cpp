#include <++cpp11.h>

// right-angle brackets

template<typename T> class RightAngleBracketsClass {
    public:
        T x;
};

void RightAngleBrackets() {
    RightAngleBracketsClass<RightAngleBracketsClass<int>> rav;
    rav.x.x++;
}
