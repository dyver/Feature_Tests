#include <QApplication>
#include <QtWebKit>
#include <QWebView>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    QWebView webView;

    webView.load(QUrl("qrc:///images/circle.svg"));
    webView.show();

    return a.exec();
}
