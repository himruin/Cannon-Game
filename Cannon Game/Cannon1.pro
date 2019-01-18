#-------------------------------------------------
#
# Project created by QtCreator 2015-05-29T19:24:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = Cannon
TEMPLATE = app


SOURCES += main.cpp \
    cannonfield.cpp \
    angle.cpp \
    force.cpp \
    drag.cpp \
    mass.cpp \
    dialog.cpp \
    wind.cpp \
    windangle.cpp \
    gameboard.cpp

HEADERS  += \
    cannonfield.h \
    force.h \
    angle.h \
    drag.h \
    mass.h \
    dialog.h \
    wind.h \
    windangle.h \
    gameboard.h

FORMS    += \
    dialog.ui

DISTFILES += \
    crash.wav \
    cannon.wav \
    Tetris.wav \
    gameover.wav
