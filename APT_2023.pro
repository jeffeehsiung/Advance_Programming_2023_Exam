TEMPLATE = app
CONFIG += console c++20
CONFIG -= app_bundle
CONFIG += qt
QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
HEADERS += \
    Image.h \
    Media.h \
    Video.h \
    album.h

SOURCES += \
    Image.cpp \
    Video.cpp \
    album.cpp \
    main.cpp

RESOURCES += \
    resources.qrc
