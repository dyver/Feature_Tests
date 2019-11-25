#include <++c.h>

// constexpr - generalized and guaranteed constant expressions

constexpr int getConstValue() { return 42; }

class ConstExpression {
    public:
        constexpr ConstExpression() : value(getConstValue()) {};
        constexpr int getValue() { return value; }
    private:
        int value;
};

void ConstExpr() {
    const int constValue = getConstValue();
    ConstExpression ce;
    const int constValue2 = ce.getValue();
    int i = constValue + constValue2;
    (void)i;
    int fixedSizeArray[getConstValue()];
    (void)fixedSizeArray;
    int fixedSizeArray2[ConstExpression().getValue()];
    (void)fixedSizeArray2;
}
