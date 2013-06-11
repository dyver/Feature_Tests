#ifndef REALIZATION_H
#define REALIZATION_H

#include "../PluginHost/interface.h"

class Realization : public Interface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "ru.analytic.Nemesis.Interface/1.0" FILE "interface.json")
    Q_INTERFACES(Interface)
    public:
        Realization();
        std::string getName();
        int getData();
    private:
        int data;
};

#endif // REALIZATION_H
