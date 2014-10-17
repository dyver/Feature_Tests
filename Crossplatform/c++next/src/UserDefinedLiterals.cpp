#include <string>
#include <sstream>

#include <++c.h>

// user-defined literals

class ClassUsesLiterals {
    public:
        ClassUsesLiterals(int aa, int bb) : a(aa), b(bb) {}
        int getA() { return a; }
    private:
        int a;
        int b;
};

// note space after "" - not required by standard
ClassUsesLiterals operator"" _cul(const char* p, size_t) {
    std::stringstream ss(p);
    int result;
    ss >> result;
    return ClassUsesLiterals(result, 0);
}

void UserDefinedLiterals() {
    auto c = "42"_cul;
    outHeader("User defined literals");
    outIdent();
    std::cout
        << "member of class, constructed from user defined string: "
        << c.getA()
        << std::endl;
}
