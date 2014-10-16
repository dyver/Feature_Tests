TEMPLATE = app
TARGET = PluginHost
QT -= gui
CONFIG -= debug_and_release
CONFIG *= silent console
QMAKE_CXXFLAGS += -std=c++11 -pedantic -Wall -Wextra -Werror

HEADERS = interface.h
SOURCES = main.cpp
