TARGET = UI
QT *= widgets uitools

CONFIG *= silent
CONFIG -= debug_and_release
windows : CONFIG *= console
QMAKE_CXXFLAGS += -std=c++11 -pedantic -Wall -Wextra -Werror

HEADERS = \
    UIClass.h \
    Form.h \
    UIInheritedClass.h \
    UIAggregateClass.h \
    UILoader.h \

SOURCES = \
    Main.cpp \
    UIClass.cpp \
    Form.cpp \
    UIInheritedClass.cpp \
    UIAggregateClass.cpp \
    UILoader.cpp \

FORMS = \
    Form.ui \

RESOURCES = \
    UI.qrc \

OTHER_FILES = \
    README \
