#include <memory> // for shared_ptr

#include <++c.h>

// shared_ptr

void SharedPtr() {
    struct Object {
        Object() { std::cout << "(Object ctor)  " << std::flush; }
        ~Object() { std::cout << "(Object dtor)  " << std::flush; }
    };
    outHeader("shared_ptr");
    outIdent();
    std::cout << "(Creating Object)  " << std::flush;
    std::shared_ptr<Object> sp(new Object);
    {
        std::cout << "(1st Sharing Object ownership)  " << std::flush;
        std::shared_ptr<Object> sp2(sp);
        {
            std::cout << "(2nd Sharing Object ownership)  " << std::flush;
            std::shared_ptr<Object> sp3(sp);
        }
    }
    std::cout << std::endl;
}
