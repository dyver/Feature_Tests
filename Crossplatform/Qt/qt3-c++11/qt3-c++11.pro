TEMPLATE = app
TARGET = qt3-c++11
CONFIG += thread
QMAKE_CXXFLAGS += -std=c++11 -pedantic-errors -Wall -Wextra

HEADERS = main.h
SOURCES = main.cpp
FORMS = mydialog.ui
