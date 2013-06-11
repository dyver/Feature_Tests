#include <iostream>
#include "header.h"

using namespace std;

using namespace cmn;

typedef varray<varray<int> > VVI;
class Test
{
    public:
        Test()
        {
            VVI vva1(5);
            for (int i = 0; i < vva1.getSize(); ++i) {
                varray<int> tmp(i);
                for (int j = 0; j < tmp.getSize(); ++j) {
                    tmp.getBuffer()[j] = j;
                }
                vva1.getBuffer()[i] = tmp;
            }
            data = vva1;
        }

        VVI get()
        {
            return data.clone();
        }
    private:
        VVI data;
};

int main()
{
    cout << endl;

    cout << "Simple varray:" << endl << endl;

    varray<int> va1(10);
    for (int i = 0; i < va1.getSize(); ++i) {
        va1.getBuffer()[i] = i;
    }

    cout << "Before moving: 'va1': Size = " << va1.getSize() << ", Content: ";
    for (int i = 0; i < va1.getSize(); ++i) {
        cout << va1.getBuffer()[i] << " ^ ";
    }
    cout << endl;

    varray<int> va2(va1);

    cout << "After moving: 'va1': Size = " << va1.getSize() << ", Content: ";
    for (int i = 0; i < va1.getSize(); ++i) {
        cout << va1.getBuffer()[i] << " ^ ";
    }
    cout << endl;
    cout << "After moving: 'va2': Size = " << va2.getSize() << ", Content: ";
    for (int i = 0; i < va2.getSize(); ++i) {
        cout << va2.getBuffer()[i] << " ^ ";
    }
    cout << endl;

    cout << "Matroska varray:" << endl << endl;

    varray<varray<int> > vva1(5);
    for (int i = 0; i < vva1.getSize(); ++i) {
        varray<int> tmp(i);
        for (int j = 0; j < tmp.getSize(); ++j) {
            tmp.getBuffer()[j] = j;
        }
        vva1.getBuffer()[i] = tmp;
    }

    cout << "Before moving: 'vva1': Size = " << vva1.getSize() << ", Content: " << endl;
    for (int i = 0; i < vva1.getSize(); ++i) {
        cout << "Size = " << vva1.getBuffer()[i].getSize() << ", Content: ";
        for (int j = 0; j < vva1.getBuffer()[i].getSize(); ++j) {
            cout << vva1.getBuffer()[i].getBuffer()[j] << " ^ ";
        }
        cout << endl;
    }
    cout << endl;

    varray<varray<int> > vva2(vva1);

    cout << "After moving: 'vva1': Size = " << vva1.getSize() << ", Content: " << endl;
    for (int i = 0; i < vva1.getSize(); ++i) {
        cout << "Size = " << vva1.getBuffer()[i].getSize() << ", Content: ";
        for (int j = 0; j < vva1.getBuffer()[i].getSize(); ++j) {
            cout << vva1.getBuffer()[i].getBuffer()[j] << " ^ ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "After moving: 'vva2': Size = " << vva2.getSize() << ", Content: " << endl;
    for (int i = 0; i < vva2.getSize(); ++i) {
        cout << "Size = " << vva2.getBuffer()[i].getSize() << ", Content: ";
        for (int j = 0; j < vva2.getBuffer()[i].getSize(); ++j) {
            cout << vva2.getBuffer()[i].getBuffer()[j] << " ^ ";
        }
        cout << endl;
    }
    cout << endl;

    Test test;
    cout << "!!!!!! " << test.get().getSize() << endl;
    cout << "$$$$$$ " << test.get().getSize() << endl;

    cout << endl;

    return 0;
}
