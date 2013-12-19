QMAKE_CXXFLAGS += -std=c++11 -pedantic -Wall -Wextra -Werror
TEMPLATE = app
TARGET = hello
INCLUDEPATH += .

# Input
SOURCES = main.cpp
QT += widgets
