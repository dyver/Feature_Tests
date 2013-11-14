QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = app
TARGET = qt3-c++11
INCLUDEPATH += .

CONFIG += thread

# Input
HEADERS += main.h
SOURCES += main.cpp

FORMS   = mydialog.ui
