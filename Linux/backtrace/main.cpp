#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstdlib>
#include <execinfo.h> // for backtrace*()

using namespace std;

class Class {
    public:
        Class() {
            i = 0;
        }
        long function(int i) {
            this->i =  i;
            throw runtime_error("Test exception");
            return this->i;
        }
    private:
        int i;
};

void dumpBacktrace() {
    vector<void*> buffer(100);

    int nptrs = backtrace(buffer.data(), buffer.size());
    cout << "backtrace() returned " << nptrs << " addresses" << endl;

    backtrace_symbols_fd(buffer.data(), nptrs, 1);
}


int main() {
    try {
        Class c;
        c.function(1);
    } catch(const exception& e) {
        cout << "Catched exception: " << e.what() << endl;
        dumpBacktrace();
    }
    return 0;
}
