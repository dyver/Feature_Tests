#include <iostream>
#include <stdexcept>

using namespace std;

class C
{
    public:
        C() { cout << "Ctor" << endl; throw std::runtime_error("11111"); }
        ~C() { cout << "Dtor" << endl; }
};

C c;

int main()
{
    C c;
    exit(0);
    return 0;
}