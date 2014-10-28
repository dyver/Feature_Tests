TEMPLATE = lib

TARGET = SharedLibrary
QT = core

CONFIG *= silent
CONFIG -= debug_and_release
windows : CONFIG *= console
QMAKE_CXXFLAGS += -std=c++11 -pedantic-errors -Wall -Wextra -Werror

INCLUDEPATH += .

HEADERS = SharedLibrary.h

SOURCES = SharedLibrary.cpp
