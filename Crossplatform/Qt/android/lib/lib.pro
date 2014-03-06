QMAKE_CXXFLAGS += -std=c++11 -pedantic -Wall -Wextra -Werror

QT = core

TEMPLATE = lib
TARGET = SharedLibrary

INCLUDEPATH += .

HEADERS = SharedLibrary.h

SOURCES = SharedLibrary.cpp
