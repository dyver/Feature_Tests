#include <++c.h>

// inline namespace

namespace InlineNamespaceV1 {
    inline void f() {}
}

inline namespace InlineNamespaceV2 {
    inline void f() {}
}

namespace UserInlineNamspace {
    // #include "InlineNamespaceV1.h"
    // #include "InlineNamespaceV2.h"
}

void InlineNamespace() {
    using namespace UserInlineNamspace;
    InlineNamespaceV1::f();
    InlineNamespaceV2::f();
    f();
}
