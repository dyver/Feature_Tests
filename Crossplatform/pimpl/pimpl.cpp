#include <iostream>

using namespace std;

#include "pimpl.h"
#include "pimpl.inl"

Pimpl::Pimpl()
        : imp(new Imp())
{
    cout << "Pimpl::Pimpl()" << endl;
}

Pimpl::~Pimpl()
{
    cout << "Pimpl::~Pimpl()" << endl;
}
