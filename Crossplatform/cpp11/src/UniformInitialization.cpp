#include <++cpp11.h>

// uniform initialization syntax and semantics

struct UniformInitStruct {
    int x;
    double y;
};

class UniformInitClass {
    public:
        UniformInitClass(int x, double y) : x_{x}, y_{y} {}
        UniformInitStruct toUniformInitStruct() { return { x_, y_ }; }
    private:
        int x_;
        double y_;
};

void UniformInitialization() {
    UniformInitStruct uis{5, 3.2};
    uis.x++;
    UniformInitClass uic = {2, 4.3};
    UniformInitStruct uis2(uic.toUniformInitStruct());
    outHeader("uniform initialization syntax and semantics");
    outIdent();
    std::cout
        << "UniformInitStruct.x = " << uis2.x
        << "UniformInitStruct.y = " << uis2.y
        << std::endl;
    std::vector<int> uivec{4}; // one element with value 4
}
