#include <++cpp11.h>

// long long - a longer integer

void LongLong() {
    // at least 64 bits guaranteed
    long long longLongInteger = 9223372036854775807LL;
    outHeader("long long - a longer integer");
    outIdent();
    std::cout
        << "value: " << ++longLongInteger
        << std::endl;
}
