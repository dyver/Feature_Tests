QMAKE_CXXFLAGS += -std=c++0x

TEMPLATE = lib
CONFIG += plugin

QT -= gui
INCLUDEPATH += .

SOURCES += \
    realization.cpp

HEADERS += \
    ../PluginHost/interface.h \
    realization.h
