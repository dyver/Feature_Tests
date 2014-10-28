TEMPLATE = app

TARGET = Android
QT *= widgets

CONFIG *= silent
CONFIG -= debug_and_release
windows : CONFIG *= console
QMAKE_CXXFLAGS += -std=c++11 -pedantic-errors -Wall -Wextra -Werror

INCLUDEPATH += ../lib

LIBS += -L../lib

LIBS += -lSharedLibrary

ANDROID_EXTRA_LIBS = $${OUT_PWD}/../lib/libSharedLibrary.so

SOURCES = main.cpp

RESOURCES = resources.qrc

READONLY_FILES = ReadonlyFile.txt

android {
    READONLY_FILES_INSTALL_PATH=/assets/ReadOnly
} else {
    READONLY_FILES_INSTALL_PATH=$${OUT_PWD}/ReadOnly
}

readonly_files.path = $${READONLY_FILES_INSTALL_PATH}
readonly_files.files = $${READONLY_FILES}
readonly_files.depends += FORCE

INSTALLS += readonly_files

!android : QMAKE_POST_LINK += make install

ANDROID_PACKAGE_SOURCE_DIR = $${PWD}

OTHER_FILES += \
    android/AndroidManifest.xml \
    $${READONLY_FILES} \
