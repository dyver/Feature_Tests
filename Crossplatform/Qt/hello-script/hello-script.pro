TARGET = hello-script
QT *= widgets script
CONFIG -= debug_and_release
CONFIG *= silent console
QMAKE_CXXFLAGS += -std=c++11 -pedantic -Wall -Wextra -Werror

SOURCES = main.cpp
RESOURCES = hello-script.qrc
OTHER_FILES = hello-script.js hello-script1_ru.ts
TRANSLATIONS = hello-script_ru.ts hello-script1_ru.ts
