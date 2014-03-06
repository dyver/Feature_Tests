#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLayout>
#include <QFile>
#include <QDir>
#include <QPixmap>
#include <QTextEdit>
#include <QStandardPaths>
#include <QDebug>

#include <../lib/SharedLibrary.h>

int main(int argc, char** argv) {
    QCoreApplication::setOrganizationName("ru.dyver.nik");
    QCoreApplication::setApplicationName("Android");

    QApplication app(argc, argv);

    // Читаем данные из файла, используя систему "assets"
    #if defined(Q_OS_ANDROID)
        const char* readonlyFileName = "assets:/ReadOnly/ReadonlyFile.txt";
    #else
        const char* readonlyFileName = "./ReadOnly/ReadonlyFile.txt";
    #endif
    QFile readonlyFile(readonlyFileName);
    QByteArray line("Пустая строка");
    if (readonlyFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        line = "<h3>" + readonlyFile.readLine() + "</h3>";
    }
    readonlyFile.close();

    QString contentString(line);

    // Читаем из файла и записываем данные в файл
    QString writableDirectory = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
    QDir().mkpath(writableDirectory);
    QString writableFileName = QString(writableDirectory) + "/WritableFile.txt";
    QString data;
    QFile writableFile(writableFileName);
    if (writableFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        data = writableFile.readLine();
    }
    contentString += QString("Счётчик из записываемого файла: ") + "<h5>" + data + "</h5>";
    writableFile.close();
    int counter = data.toInt();
    if (writableFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        writableFile.write(QString::number(counter + 1).toLocal8Bit());
    }
    writableFile.close();

    contentString += "Данные из файла ресурсов, прочитанного библиотекой: ";
    contentString += "<h5>" + SharedLibrary::getFileContent(":/text/ReadonlyFile.txt") + "</h5>";

    contentString += "<small>";
    contentString += QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    contentString += "<br/>";
    contentString += QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    contentString += "<br/>";
    contentString += QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
    contentString += "<br/>";
    contentString += QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
    contentString += "<br/>";
    contentString += QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation);
    contentString += "<br/>";
    contentString += "</small>";
    auto content = new QTextEdit{contentString};
    content->setAlignment(Qt::AlignCenter);
    auto header = new QLabel{QString("<h2><i>Привет</i> <font color=red>Аналитик!</font></h2>")};
    header->setAlignment(Qt::AlignCenter);

    // Получаем данные из файла ресурсов
    auto picture = new QPixmap(":/images/icon.png");
    auto pictureLabel = new QLabel;
    auto pictureLabelBuddy = new QLabel("Из файла ресурсов");
    pictureLabelBuddy->setAlignment(Qt::AlignCenter);
    pictureLabel->setPixmap(*picture);
    pictureLabel->setAlignment(Qt::AlignCenter);

    auto button = new QPushButton{"OK"};
    QObject::connect(button, &QPushButton::clicked, &app, &QApplication::exit);
    auto layout = new QVBoxLayout();
    layout->addWidget(header);
    layout->addWidget(content);
    layout->addWidget(pictureLabelBuddy);
    layout->addWidget(pictureLabel);
    layout->addWidget(button);
    auto window = new QWidget;
    window->setWindowTitle("Hello!");
    window->setLayout(layout);
    window->show();
    return app.exec();
}
