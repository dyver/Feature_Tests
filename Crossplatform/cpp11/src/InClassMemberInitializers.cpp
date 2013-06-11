#include <++cpp11.h>

// in-class member initializers

class InClassMemberInitializersClass {
    public:
        InClassMemberInitializersClass() {} // defaults will be used
        InClassMemberInitializersClass(int aa) : a{aa} {} // overrides defaults
    private:
        int a = 10; // default value used by default constructor
};

void InClassMemberInitializers() {
    InClassMemberInitializersClass c;
}
