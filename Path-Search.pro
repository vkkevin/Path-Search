QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11
DEFINES += QT_DEPRECATED_WARNINGS

TEMPLATE = app
TARGET = Path-Search
INCLUDEPATH += src

SOURCE_DIR = ./resource

RESOURCES += resource.qrc
RC_FILE += $${SOURCE_DIR}/path.rc

include(./src/src.pri)
