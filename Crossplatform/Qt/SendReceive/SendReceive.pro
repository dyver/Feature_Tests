TARGET = SendReceive
QT *= widgets network

CONFIG *= silent
CONFIG -= debug_and_release
windows : CONFIG *= console
QMAKE_CXXFLAGS += -std=c++11 -pedantic-errors -Wall -Wextra -Werror

SOURCES = \
    Main.cpp \
    MainWindow.cpp \

HEADERS = \
    MainWindow.h \

FORMS = MainWindow.ui
