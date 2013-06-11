#include <++cpp11.h>

// noexcept - preventing exception propagation

void noExceptFunction() noexcept {
    throw int();
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
