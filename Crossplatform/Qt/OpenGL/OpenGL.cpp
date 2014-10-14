#include <QMouseEvent>

#include <OpenGL.h>

OpenGL::OpenGL(QWidget* parent) :
    QGLWidget(parent)
{
}

void OpenGL::initializeGL() {
    qglClearColor(Qt::black);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    pyramidList = createPyramid(1.2);
}

void OpenGL::resizeGL(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 10.0);
}

void OpenGL::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -3.0);
    glRotatef(xRotate, 1.0, 0.0, 0.0);
    glRotatef(yRotate, 0.0, 1.0, 0.0);
    glCallList(pyramidList);
}

void OpenGL::mousePressEvent(QMouseEvent* pe) {
    position = pe->pos();
}

void OpenGL::mouseMoveEvent(QMouseEvent* pe) {
    xRotate += 180 * (pe->y() - position.y()) / height();
    yRotate += 180 * (pe->x() - position.x()) / width();
    updateGL();
    position = pe->pos();
}

GLuint OpenGL::createPyramid(GLfloat size) {
    auto n = glGenLists(1);
    glNewList(n, GL_COMPILE);
        glBegin(GL_TRIANGLE_FAN);
            qglColor(Qt::green);
            glVertex3f(0, size, 0);
            glVertex3f(-size, -size, size);
            glVertex3f(size, -size, size);
            qglColor(Qt::yellow);
            glVertex3f(size, -size, -size);
            qglColor(Qt::blue);
            glVertex3f(-size, -size, -size);
            qglColor(Qt::white);
            glVertex3f(-size, -size, size);
        glEnd();
        glBegin(GL_QUADS);
            qglColor(Qt::red);
            glVertex3f(-size, -size, size);
            glVertex3f(size, -size, size);
            glVertex3f(size, -size, -size);
            glVertex3f(-size, -size, -size);
        glEnd();
    glEndList();
    return n;
}
