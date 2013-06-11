QMAKE_CXXFLAGS += -std=c++0x -pedantic-errors -Wall -Wextra -Werror

TEMPLATE = app
INCLUDEPATH += .

SOURCES += main.cpp

HEADERS += \
    interface.h
