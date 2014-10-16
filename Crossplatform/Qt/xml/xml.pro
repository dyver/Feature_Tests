TARGET = xml
QT *= widgets xml
CONFIG -= debug_and_release
CONFIG *= silent console
QMAKE_CXXFLAGS += -std=c++11 -pedantic -Wall -Wextra -Werror

SOURCES = main.cpp
RESOURCES = xml.qrc
