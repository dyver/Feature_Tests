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

int main(int argc, char* argv[]) {
    QCoreApplication::setOrganizationName("ru.dyver.nik");
    QCoreApplication::setApplicationName("Android");

    QApplication application(argc, argv);

    // Читаем данные из файла, используя систему "assets"
    #if defined(Q_OS_ANDROID)
        const char* readonlyFileName = "assets:/ReadOnly/ReadonlyFile.txt";
    #else
        const char* readonlyFileName = "./ReadOnly/ReadonlyFile.txt";
    #endif
    QFile readonlyFile(readonlyFileName);
    QByteArray line("Read-only файл не обнаружен<br/>");
    if (readonlyFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        line = readonlyFile.readLine() + "<br/>";
    }
    readonlyFile.close();

    QString contentString("<em>Данные из файла: </em><b>" + line + "</b>");

    // Читаем из файла и записываем данные в файл
    QString writableDirectory = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
    QDir().mkpath(writableDirectory);
    QString writableFileName = QString(writableDirectory) + "/WritableFile.txt";
    QString data{"Файл не обнаружен."};
    QFile writableFile(writableFileName);
    if (writableFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        data = writableFile.readLine();
    }
    contentString += "<em>Счётчик из записываемого файла: </em><b>" + data + "</b><br/>";
    writableFile.close();
    int counter = data.toInt();
    if (writableFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        writableFile.write(QString::number(counter + 1).toLocal8Bit());
    }
    writableFile.close();

    contentString += "<em>Данные из файла ресурсов, прочитанного библиотекой: </em>";
    contentString += "<b>" + SharedLibrary::getFileContent(":/text/ReadonlyFile.txt") + "</b><br/>";

    contentString += "<em>Стандартные пути: <br/><small>";
    contentString += "<em>HomeLocation:</em><br/>";
    contentString += QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "<br/>";
    contentString += "<em>DataLocation:</em><br/>";
    contentString += QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "<br/>";
    contentString += "<em>GenericDataLocation:</em><br/>";
    contentString += QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + "<br/>";
    contentString += "<em>ConfigLocation:</em><br/>";
    contentString += QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "<br/>";
    contentString += "<em>GenericConfigLocation:</em><br/>";
    contentString += QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + "<br/>";
    contentString += "</small>";
    auto content = new QTextEdit{contentString};
    content->setAlignment(Qt::AlignLeft);
    auto header = new QLabel{"<h2><em>Привет,</em> <font color=red>братья по разуму</font> !</h2>"};
    header->setAlignment(Qt::AlignCenter);

    // Получаем данные из файла ресурсов
    auto picture = new QPixmap(":/images/icon.png");
    auto pictureLabel = new QLabel;
    auto pictureLabelBuddy = new QLabel("Из файла ресурсов");
    pictureLabelBuddy->setAlignment(Qt::AlignCenter);
    pictureLabel->setPixmap(*picture);
    pictureLabel->setAlignment(Qt::AlignCenter);

    QApplication::setWindowIcon(QIcon(":/images/icon.png"));
    auto closeButton = new QPushButton{"Закрыть"};
    QObject::connect(closeButton, &QPushButton::clicked, &application, &QApplication::exit);
    auto cleanButton = new QPushButton{"Удалить записываемый файл"};
    QObject::connect(cleanButton, &QPushButton::clicked, [&]{ QDir().remove(writableFileName); });
    auto layout = new QVBoxLayout;
    layout->addWidget(header);
    layout->addWidget(content);
    layout->addWidget(pictureLabelBuddy);
    layout->addWidget(pictureLabel);
    layout->addWidget(cleanButton);
    layout->addWidget(closeButton);
    auto window = new QWidget;
    window->setWindowTitle("Hello!");
    window->setLayout(layout);
    closeButton->setDefault(true);
    closeButton->setFocus();
    window->show();
    return application.exec();
}
