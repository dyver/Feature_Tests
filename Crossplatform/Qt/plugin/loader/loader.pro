TEMPLATE = app
TARGET = loader
QT = core

CONFIG *= silent
CONFIG -= debug_and_release
windows : CONFIG *= console
QMAKE_CXXFLAGS += -std=c++11 -pedantic-errors -Wall -Wextra -Werror

HEADERS = ../interface/interface.h
SOURCES = main.cpp
