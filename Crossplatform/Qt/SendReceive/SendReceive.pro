TARGET = SendReceive
QT *= widgets network
CONFIG -= debug_and_release
CONFIG *= silent console
QMAKE_CXXFLAGS += -std=c++11 -pedantic -Wall -Wextra -Werror

SOURCES = \
    Main.cpp \
    MainWindow.cpp \

HEADERS = \
    MainWindow.h \

FORMS = MainWindow.ui
