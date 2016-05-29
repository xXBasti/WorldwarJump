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
<<<<<<< HEAD
    GameplayInterface.cpp

HEADERS  += mainwindow.h \
    GameplayInterface.h
=======
    input.cpp \
    gameworld.cpp

HEADERS  += mainwindow.h \
    input.h \
    gameworld.h
>>>>>>> 8e396a4565f364950c27be9e42266f1e11b4f1d0

FORMS    += mainwindow.ui

unix|win32: LIBS += -L$$PWD/'../../../../../../Program Files (x86)/Windows Kits/10/Lib/10.0.10586.0/um/x64/' -lshell32

INCLUDEPATH += $$PWD/'../../../../../../Program Files (x86)/Windows Kits/10/Lib/10.0.10586.0/um/x64'
DEPENDPATH += $$PWD/'../../../../../../Program Files (x86)/Windows Kits/10/Lib/10.0.10586.0/um/x64'
