#include <memory> // for unique_ptr

#include <++c.h>

// unique_ptr

void UniquePtr() {
    struct Exception {};
    struct Object {
        Object() { std::cout << "(Object ctor)  " << std::flush; }
        ~Object() { std::cout << "(Object dtor)  " << std::flush; }
        void f() {
            std::cout << "(Object f() throws)  " << std::flush;
            throw Exception();
        }
    };
    outHeader("unique_ptr");
    outIdent();
    try {
        std::unique_ptr<Object> up(new Object);
        up->f();
    } catch (Exception) {}
    std::cout << std::endl;
}
