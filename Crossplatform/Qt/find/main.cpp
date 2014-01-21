#include <QApplication>
#include  <QStyleFactory>

#include <findDialog.h>

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  //QApplication::setStyle(new Style);
  QApplication::setStyle(QStyleFactory::create("windows"));
  FindDialog* dialog = new FindDialog;
  dialog->show();
  return app.exec();
}
