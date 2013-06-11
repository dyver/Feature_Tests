#include <++cpp11.h>

// suffix return type syntax

inline auto suffixFunction() -> int {
    return 42;
}

class SuffixClass {
    public:
        class SuffixInnerClass {};
        SuffixInnerClass* inner();
};

inline auto SuffixClass::inner() -> SuffixInnerClass* {
    return new SuffixInnerClass();
}

void SuffixReturnTypeSyntax() {
    SuffixClass sc;
    SuffixClass::SuffixInnerClass* sic = sc.inner();
    delete sic;
}
