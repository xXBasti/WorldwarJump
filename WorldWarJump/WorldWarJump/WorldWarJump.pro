#-------------------------------------------------
#
# Project created by QtCreator 2016-05-25T16:51:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WorldWarJump
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    GameplayInterface.cpp \
    input.cpp \
    gameworld.cpp \
    worldobject.cpp \
    physicscalc.cpp

HEADERS  += mainwindow.h \
    GameplayInterface.h \
    input.h \
    gameworld.h \
    worldobject.h \
    physicscalc.h


FORMS    += mainwindow.ui

unix|win32: LIBS += -L$$PWD/'../../../../../../Program Files (x86)/Windows Kits/10/Lib/10.0.10586.0/um/x64/' -lshell32

INCLUDEPATH += $$PWD/'../../../../../../Program Files (x86)/Windows Kits/10/Lib/10.0.10586.0/um/x64'
DEPENDPATH += $$PWD/'../../../../../../Program Files (x86)/Windows Kits/10/Lib/10.0.10586.0/um/x64'
