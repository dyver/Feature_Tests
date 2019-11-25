#include <QtWidgets>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QDesktopWidget* desktop = QApplication::desktop();
    for (int i = 0; i < desktop->numScreens(); ++i) {
        qInfo() << "Screen #" << i << ":"
            << " width:" << desktop->screenGeometry(i).width()
            << " height:" << desktop->screenGeometry(i).height()
        ;
    }

    auto screens = QGuiApplication::screens();
    int selectedScreenIndex = screens.size() - 1;
    auto selectedScreen = screens[selectedScreenIndex];

    QObject::connect(&app, &QGuiApplication::screenAdded, [](QScreen* ) { qInfo() << "Added screen #"; });

    QLabel central;
    auto pic = selectedScreen->grabWindow(0);
    central.setPixmap(pic.scaled(central.size()));
    central.show();

    return app.exec();
}
