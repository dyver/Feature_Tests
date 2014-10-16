TEMPLATE = lib
TARGET = SharedLibrary

QT -= gui
QT = core

CONFIG -= debug_and_release
CONFIG *= silent console
QMAKE_CXXFLAGS += -std=c++11 -pedantic -Wall -Wextra -Werror

INCLUDEPATH += .

HEADERS = SharedLibrary.h

SOURCES = SharedLibrary.cpp
