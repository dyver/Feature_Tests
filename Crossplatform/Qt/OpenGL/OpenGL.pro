TARGET = OpenGL
QT *= widgets opengl
CONFIG -= debug_and_release
CONFIG *= silent console
QMAKE_CXXFLAGS += -std=c++11 -pedantic -Wall -Wextra -Werror

SOURCES = \
    main.cpp \
    OpenGL.cpp \

HEADERS = \
    OpenGL.h \
