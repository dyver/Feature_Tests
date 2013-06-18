#include <iostream>
#include <memory>

using namespace std;

class Interface {
    public:
        virtual ~Interface() {}
        virtual void hello() = 0;
};

template <class T> class Base : public Interface {
    public:
        void hello() {
            static_cast<T*>(this)->do_hello();
        }
    private:
        void do_hello() {
            cout << "Base::hello()" << endl;
        }
};

class First : public Base<First> {
    public:
        void do_hello() {
            cout << "First::hello()" << endl;
        }
};

class Second : public Base<Second> {
};

int main() {
    typedef std::auto_ptr<Interface> InterfacePtr;

    InterfacePtr i1(new First);
    InterfacePtr i2(new Second);

    i1->hello();
    i2->hello();

    return 0;
}
