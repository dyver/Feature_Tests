TARGET = OpenGL
QT *= widgets opengl
CONFIG *= silent
QMAKE_CXXFLAGS += -std=c++11

SOURCES = \
    main.cpp \
    OpenGL.cpp

HEADERS = \
    OpenGL.h
