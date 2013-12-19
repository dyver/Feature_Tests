#include <QApplication>
#include <QLabel>
#include <QTextCodec>
#include <QDir>
#include <QTextEdit>

#include <sstream>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF8"));
//    QLabel label("<h2><i>Привет</i> <font color=red>Qt!</font></h2>");
//    label.show();

    {
        ofstream os("/data/data/org.qtproject.example.hello/files/test.txt");
        os << "Hello!" << endl;
    }
    QDir dir("/data/app/org.qtproject.example.hello");
    dir.setFilter(QDir::Files | QDir::Dirs | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Size | QDir::Reversed);
    QFileInfoList list = dir.entryInfoList();
//    std::cout << "     Bytes Filename" << std::endl;
    stringstream ss;
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        ss << qPrintable(QString("%1 %2").arg(fileInfo.size(), 10)
                                                .arg(fileInfo.fileName()));
        ss << '\n';
    }
    //QLabel label(ss.str().c_str());
    //label.show();
    QTextEdit te;
    te.setFont(QFont("Monospace"));
    te.setPlainText(ss.str().c_str());
    te.setAcceptRichText(true);
    te.show();
    return app.exec();
}
