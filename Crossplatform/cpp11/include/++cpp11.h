#ifndef CPP11_H
#define CPP11_H

#include <iostream> // for console output
#include <vector> // for container tests

#include "declarations.h"

// helpers for outputting information

inline void outHeader(std::string s)
{
    std::cout << std::endl << s << std::endl;
}

inline void outIdent()
{
    std::cout << "   ";
}

inline void outTail()
{
    std::cout << std::endl;
}

#endif // CPP11_H
