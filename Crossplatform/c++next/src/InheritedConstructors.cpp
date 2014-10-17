#include <++c.h>

// inherited constructors

class InheritedConstructorBase {
    public:
        InheritedConstructorBase() {}
};

class InheritedConstructorDerived : public InheritedConstructorBase {
    public:
        using InheritedConstructorBase::InheritedConstructorBase;
};

void InheritedConstructors() {
    InheritedConstructorDerived c;
    (void)c;
}
