#include <QApplication>
#include <QLabel>
#include <QTextCodec>

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF8"));
    QLabel label("<h2><i>Привет</i> <font color=red>Qt!</font></h2>");
    label.show();
    return app.exec();
}
