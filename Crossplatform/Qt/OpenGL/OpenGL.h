#ifndef OPENGL_H
#define OPENGL_H

#include <QGLWidget>

class OpenGL : public QGLWidget {
    Q_OBJECT
    public:
        explicit OpenGL(QWidget* parent = nullptr);
    protected:
        void initializeGL();
        void resizeGL(int w, int h);
        void paintGL();
        void mousePressEvent(QMouseEvent* pe);
        void mouseMoveEvent(QMouseEvent* pe);
    private:
        GLuint createPyramid(GLfloat size = 1.0f);
        GLuint pyramidList = 0;
        GLfloat xRotate = 0;
        GLfloat yRotate = 0;
        QPoint position;
};

#endif // OPENGL_H
