#include <QtWidgets>

#include <OpenGL.h>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    auto ogl = new OpenGL;
    ogl->showFullScreen();
    return app.exec();
}
