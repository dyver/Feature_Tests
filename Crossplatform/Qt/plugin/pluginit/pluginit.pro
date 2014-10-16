TEMPLATE = lib
TARGET = pluginit
QT -= gui
CONFIG -= debug_and_release
CONFIG *= silent console
CONFIG *= plugin
QMAKE_CXXFLAGS += -std=c++11 -pedantic -Wall -Wextra -Werror

SOURCES = \
    realization.cpp \

HEADERS = \
    ../PluginHost/interface.h \
    realization.h \
