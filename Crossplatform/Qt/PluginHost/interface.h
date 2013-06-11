#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>

#include <QObject>

class Interface : public QObject
{
    public:
        virtual std::string getName() = 0;
        virtual int getData() = 0;
};

Q_DECLARE_INTERFACE(Interface, "ru.analytic.Nemesis.Interface/1.0")

#endif // INTERFACE_H
