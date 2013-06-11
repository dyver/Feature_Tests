#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

class Base {
    public:
        Base() {
            cout << "Base" << endl;
        }
        virtual ~Base() {
            cout << "~Base" << endl;
        }
        virtual void virtualFunction() {
            cout << "Base::virtualFunction" << endl;
        }
        void overloadedFunction() {
            cout << "Base::overloadedFunction" << endl;
        }
};

class Derived : public Base {
    public:
        Derived() {
            cout << "Derived" << endl;
        }
        ~Derived() {
            cout << "~Derived" << endl;
        }
        void virtualFunction() {
            cout << "Derived::virtualFunction" << endl;
            overloadedFunction();
        }
        void overloadedFunction() {
            cout << "Derived::overloadedFunction" << endl;
        }
};

int main(void) {
    Base* b = new Derived();
    b->virtualFunction();
    b->overloadedFunction();
    delete b;

    return 0;
}