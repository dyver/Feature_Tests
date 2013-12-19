#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLayout>

int main(int argc, char** argv) {
     QApplication app(argc, argv);
     auto label = new QLabel{"<h2><i>Привет</i> <font color=red>Аналитик!</font></h2>"};
     label->setAlignment(Qt::AlignCenter);
     auto button = new QPushButton{"OK"};
     QObject::connect(button, &QPushButton::clicked, &app, &QApplication::exit);
     auto layout = new QVBoxLayout();
     layout->addWidget(label);
     layout->addWidget(button);
     auto window = new QWidget;
     window->setWindowTitle("Hello!");
     layout->addWidget(label);
     window->setLayout(layout);
     window->show();
     return app.exec();
}
