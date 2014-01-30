QMAKE_CXXFLAGS += -std=c++11 -pedantic -Wall -Wextra -Werror
TEMPLATE = app
TARGET = naked

SOURCES = main.cpp
QT -= gui core
