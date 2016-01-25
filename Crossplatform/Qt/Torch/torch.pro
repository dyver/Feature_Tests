TEMPLATE = app

TARGET = Torch
QT *= widgets svg multimedia

android: !contains(QMAKE_HOST.os, Windows): CONFIG *= silent
CONFIG -= debug_and_release
windows: CONFIG *= console
QMAKE_CXXFLAGS += -std=c++14 -pedantic-errors -Wall -Wextra -Werror

SOURCES = main.cpp

RESOURCES = resources.qrc

ANDROID_PACKAGE_SOURCE_DIR = $${PWD}/android

OTHER_FILES += \
    android/AndroidManifest.xml \

