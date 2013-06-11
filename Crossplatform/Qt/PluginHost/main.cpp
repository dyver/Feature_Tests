#include <iostream>
#include <string>
#include <stdexcept>

#include <QPluginLoader>
#include <QDebug>
/*
#include "interface.h"

using namespace std;

#include <QDir>

class PluginManager
{
    public:
        //using List = QList<QString>;
        typedef QList<QString> List;
        PluginManager(const QString& p)
                : path(p)
        {
            index = 0;
            generateLibList();
        }
        void selectVersion(int i)
        {
            index = i;
        }
        template<typename T> List getNames() {
            QList<QString> res;
            for (auto i : libList) {
                QPluginLoader loader(i);
                auto p = qobject_cast<T*>(loader.instance());
                if (!p) throw runtime_error("Loading plugin");
                res << p->getName().c_str();
            }
            return res;
        }
        template<typename T> T* getObject()
        {
            if (index < 0 || index >= libList.size()) throw runtime_error("Invalid index");
            QPluginLoader loader(libList[index]);
            auto p = qobject_cast<T*>(loader.instance());
            qDebug() << loader.instance();
            if (!p) throw runtime_error("Loading plugin");
            return p;
        }
    private:
        void generateLibList()
        {
            QDir dir(path);
            if (!dir.exists()) throw runtime_error("PluginManager: no such directory");
            for (auto name : dir.entryList(QDir::Files)) {
                if (name.endsWith(".so")) {
                    libList << dir.absoluteFilePath(name);
                }
                if (name.endsWith(".dll")) {
                    libList << dir.absoluteFilePath(name);
                }
            }
            for (auto name : libList) cout << name.toStdString() << endl;
        }
        QString path;
        QList<QString> libList;
        int index;
};

class InterfaceManager : public PluginManager
{
    public:
        InterfaceManager() : PluginManager("../pluginit/") {}
        Interface* getInterface() { return getObject<Interface>(); }
};

Interface* makeInterface(int version = 0)
{
    InterfaceManager im;
    for (auto i : im.getNames<Interface>()) {
        cout << "List:::" << i.toStdString() << endl;
    }
    im.selectVersion(version);
    return im.getInterface();
}

void useInterface(Interface* interface)
{
    cout << interface->getData() << endl;
}
*/
int main(int argc, char* argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    const QString pathToLibrarys = "/home/sergey/Projects/tests/qt/pluginit/libpluginit.so";
    QPluginLoader loader(pathToLibrarys);
    qDebug() << loader.instance();

/*

    try {
        Interface* interface = makeInterface();
        useInterface(interface);
        interface = makeInterface(1);
        useInterface(interface);
    } catch (exception& e) {
        cerr << e.what() << endl;
    }
*/
    return 0;
}
