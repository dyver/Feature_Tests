#include <QtPlugin>

#include <realization.h>

Realization::Realization() {
    data = 10;
}

std::string Realization::getName() {
    return "My Name is Realization";
}

int Realization::getData() {
    ++data;
    return data;
}
