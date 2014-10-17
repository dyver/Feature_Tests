#include <++c.h>

// static (compile-time) assertions - static_assert

static_assert(sizeof(long) >= 4, "64-bits compiler required");

void StaticAssertions() {
    static_assert(true, "do not showed");
}
