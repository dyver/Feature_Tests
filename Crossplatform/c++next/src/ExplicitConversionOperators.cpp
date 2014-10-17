#include <++c.h>

// explicit conversion operators

class ExplicitConversionClass1 {
    public:
        ExplicitConversionClass1(int ii) : i{ii} {}
    private:
        int i;
};

class ExplicitConversionClass2 {
    public:
        explicit operator ExplicitConversionClass1() {
            return ExplicitConversionClass1(i);
        }
    private:
        int i;
};

void ExplicitConversionOperators() {
    ExplicitConversionClass2 ecc2;
    ExplicitConversionClass1 ecc1(ecc2); // explicit conversion
    // ExplicitConversionClass1 ecc11 = ecc2; // no implicit conversion
}
