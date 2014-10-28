TEMPLATE = lib
TARGET = pluginit
QT = core
CONFIG *= plugin

CONFIG *= silent
CONFIG -= debug_and_release
windows : CONFIG *= console
QMAKE_CXXFLAGS += -std=c++11 -pedantic-errors -Wall -Wextra -Werror

SOURCES = \
    realization.cpp \

HEADERS = \
    ../PluginHost/interface.h \
    realization.h \
