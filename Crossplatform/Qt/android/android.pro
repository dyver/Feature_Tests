TEMPLATE = app
TARGET = android
INCLUDEPATH += .

# Input
SOURCES += main.cpp
QT += widgets

OTHER_FILES += circle.svg

packetData.files = normal.bmp
packetData.path = /data/data
#$$OUT_PWD
#_PRO_FILE_PWD_

#target.path = $$TARGET_DIR
#target.files += normal.bmp
#message($$target.path)
INSTALLS += target packetData
