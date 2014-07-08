CONFIG -= debug_and_release

QMAKE_CXXFLAGS += -std=c++11 -pedantic -Wall -Wextra -Werror

CONFIG -= debug_and_release

QT = core

TEMPLATE = lib
TARGET = SharedLibrary

INCLUDEPATH += .

HEADERS = SharedLibrary.h

SOURCES = SharedLibrary.cpp
