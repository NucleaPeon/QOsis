#-------------------------------------------------
#
# Project created by QtCreator 2025-12-06T00:01:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QOsis
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        about.cpp\
        preferences.cpp

HEADERS  += mainwindow.h\
        about.h\
        preferences.h

macx { 

    LIBS += -framework Cocoa

    QT += macextras

    OBJECTIVE_SOURCES += cocoainitializer.mm
    OBJECTIVE_HEADERS += cocoainitializer.h

}


FORMS    += mainwindow.ui\
        about.ui\
        preferences.ui
