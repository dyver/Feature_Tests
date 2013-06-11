#include <cstdio> // for puts and printf

#include <++cpp11.h>

// C99 features

#define c99variadicMacros(test, ...) \
    ((!test) ? puts(#test) : printf(__VA_ARGS__))

void C99features() {
    outHeader("C99 features");
    outIdent();
    std::cout
        << "__func__ = " << __func__
        << std::endl;
    outIdent();
    std::cout
        << "__STDC_HOSTED__ = " << __STDC_HOSTED__
        << std::endl;
    _Pragma("pack()") // -> #pragma pack()
    outIdent();
    c99variadicMacros(false, "not outputted");
    outIdent();
    c99variadicMacros(true, "format string %d", 2);
    std::cout << std::endl;
}
