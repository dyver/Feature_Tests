#include <QtCore>

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);
    qDebug() << "Test";
    return app.exec();
}
