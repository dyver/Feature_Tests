#include <iostream>
#include <stdexcept>

using namespace std;

class Class {
    public:
        Class() {
            cout << "Constructor of object #" << ++getCounter() << endl;
        }
        ~Class() {
            cout << "Destructor of object #" << getCounter()-- << endl;
        }
    private:
        int& getCounter() {
            static int counter = 0;
            return counter;
        }
};

Class c;

int main() {
    Class c;
    exit(0);
    return 0;
}
