#include <stdexcept>

#include <QPluginLoader>
#include <QDir>
#include <QDebug>

#include <../interface/interface.h>

using namespace std;

class PluginManager {
    public:
        using List = QList<QString>;
        PluginManager(const QString& p)
            : path(p)
        {
            index = 0;
            generateLibList();
        }
        void selectVersion(int i) {
            index = i;
        }
        template<typename T> List getNames() {
            QList<QString> names;
            for (const auto& item : libList) {
                QPluginLoader loader(item);
                auto p = qobject_cast<T*>(loader.instance());
                if (!p) throw runtime_error("Loading plugin");
                names << p->getName().c_str();
            }
            return names;
        }
        template<typename T> T* getObject() {
            if (index < 0 or index >= libList.size()) throw runtime_error("Invalid index");
            QPluginLoader loader(libList[index]);
            auto p = qobject_cast<T*>(loader.instance());
            if (!p) throw runtime_error("Loading plugin");
            return p;
        }
    private:
        void generateLibList() {
            QDir dir(path);
            if (!dir.exists()) throw runtime_error("PluginManager: no such directory");
            for (const auto& name : dir.entryList(QDir::Files)) {
                if (name.endsWith(".so")) {
                    libList << dir.absoluteFilePath(name);
                }
                if (name.endsWith(".dll")) {
                    libList << dir.absoluteFilePath(name);
                }
            }
            qDebug() << "LibList:";
            for (const auto& name : libList) qDebug() << "  " << name;
        }
        QString path;
        QList<QString> libList;
        int index;
};

class InterfaceManager : public PluginManager {
    public:
        InterfaceManager() : PluginManager("../extension/") {}
        Interface* getInterface() { return getObject<Interface>(); }
};

Interface* makeInterface(int version = 0) {
    InterfaceManager im;
    qDebug() << "Interfaces:";
    for (const auto& i : im.getNames<Interface>()) {
        qDebug() << "  " << i;
    }
    im.selectVersion(version);
    return im.getInterface();
}

void useInterface(Interface* interface) {
    qDebug() << "Interface::getData():" << interface->getData();
}

int main() {
    try {
        auto interface = makeInterface();
        useInterface(interface);
        interface = makeInterface(1);
        useInterface(interface);
    } catch (const exception& e) {
        qCritical() << "Critical error:" << e.what();
    }
    return 0;
}
