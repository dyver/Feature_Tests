QT += core gui webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets

TARGET = svg-in-browser
TEMPLATE = app

SOURCES += main.cpp

RESOURCES = \
    svg-in-browser.qrc
