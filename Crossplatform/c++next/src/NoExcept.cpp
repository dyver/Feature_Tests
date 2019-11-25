#include <++c.h>

// noexcept - preventing exception propagation

void noExceptFunction() noexcept {
    // error: throw will always call terminate() [-Werror=terminate]
    // throw int();
}

void conditionalNoExceptFunction() noexcept(!noexcept(noExceptFunction())) {
    throw int();
}

void NoExcept() {
    try {
        // noExceptFunction(); // program will be terminated
        conditionalNoExceptFunction();
    } catch (int) {}
}
