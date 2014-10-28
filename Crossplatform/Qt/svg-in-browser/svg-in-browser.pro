TARGET = svg-in-browser
QT *= widgets webkit webkitwidgets

CONFIG *= silent
CONFIG -= debug_and_release
windows : CONFIG *= console
QMAKE_CXXFLAGS += -std=c++11 -pedantic-errors -Wall -Wextra -Werror

SOURCES = main.cpp
RESOURCES = svg-in-browser.qrc
