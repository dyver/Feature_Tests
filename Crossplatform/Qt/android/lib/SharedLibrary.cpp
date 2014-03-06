#include <QFile>
#include <QDebug>

#include <SharedLibrary.h>

namespace SharedLibrary {
    QByteArray getFileContent(const QString& readonlyFileName) {
        QFile readonlyFile(readonlyFileName);
        QByteArray line("Пустая строка");
        if (readonlyFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            line = readonlyFile.readLine();
        }
        readonlyFile.close();
        return line;
    }
}
