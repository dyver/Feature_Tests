TARGET = naked
QT -= gui core
CONFIG -= debug_and_release
CONFIG *= silent console
QMAKE_CXXFLAGS += -std=c++11 -pedantic -Wall -Wextra -Werror

SOURCES = main.cpp
