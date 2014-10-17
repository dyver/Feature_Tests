#include <++c.h>

// delegating constructors

class ClassWithDelegatingConstructors {
    public:
        ClassWithDelegatingConstructors(int new_number)
            : number(new_number) {}
        ClassWithDelegatingConstructors()
            : ClassWithDelegatingConstructors(42) {}
    private:
        int number;
};

void DelegatingConstructors() {
    ClassWithDelegatingConstructors c;
}
