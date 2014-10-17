#include <exception>

#include <++c.h>

// copying and rethrowing exceptions

inline void innerRethrowExceptionFunction() {
    throw int();
}

inline void outerRethrowExceptionFunction() {
    try {
        innerRethrowExceptionFunction();
    } catch (...) {
        //throw std::current_exception();
        std::rethrow_exception(std::current_exception());
    }
}

void CopyingExceptions() {
    try {
        outerRethrowExceptionFunction();
    } catch (int) {}
}
