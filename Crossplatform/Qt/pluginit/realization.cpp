#include "realization.h"
#include <QtPlugin>

Realization::Realization()
{
    data = 10;
}

std::string Realization::getName()
{
    return "My Name is Realization";
}

int Realization::getData()
{
    data += 1;
    return data;
}
