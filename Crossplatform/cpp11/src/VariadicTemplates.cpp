#include <++cpp11.h>

// variadic templates

inline int variadicTemplateFunction() {
    return 1;
}

template <typename T, typename ... L> int variadicTemplateFunction(T first, L ... other) {
    return first + variadicTemplateFunction(other ...);
}

// ... here must be tuples engine, but i don't understand it

void VariadicTemplates() {
    int firstArg = 10;
    double secondArg = 20.20;
    float thirdArg = 30.31;
    double result = variadicTemplateFunction(firstArg, secondArg, thirdArg);
    outHeader("variadic templates");
    outIdent();
    std::cout
        << "variadicTemplateFunction result: " << result
        << std::endl;
}
