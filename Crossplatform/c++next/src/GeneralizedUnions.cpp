#include <complex> // for unions (generalized)

#include <++c.h>

// unions (generalized)

union GeneralizedUnion {
    int i;
    std::complex<double> v; // type has ctor/dtor
};

class GeneralizedUnionContainer {
    public:
        enum class Type { number, vector }; // discriminant
        GeneralizedUnionContainer(Type t) {
            type = t;
            switch (type) {
                case Type::number:
                    i = 100;
                    break;
                case Type::vector:
                    v = { 1, 2, 3 };
                    break;
            }
        }
        void clear() {
            switch (type) {
                case Type::number:
                    break;
                case Type::vector:
                    v.clear();
                    v.~vector<int>(); // note explicit dtor call
                    break;
            }
        }
    private:
        Type type;
        union {
            int i;
            std::vector<int> v; // type has ctor/dtor
        };
};

void GeneralizedUnions() {
    // GeneralizedUnion u; // strict use forbidden cause of deleted ctor/dtor
    // Partially don't work  produces memory leaks
    //auto guc = new GeneralizedUnionContainer(GeneralizedUnionContainer::Type::vector);
    //guc->clear();
    //delete guc;
}
