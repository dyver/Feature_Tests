TEMPLATE = app
TARGET = mutithreads
DEPENDPATH += .
INCLUDEPATH += .

QMAKE_CXXFLAGS_RELEASE += -MP4

# Input
SOURCES += main.cpp file1.cpp file2.cpp
