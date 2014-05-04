#-------------------------------------------------
#
# Project created by QtCreator 2014-04-29T16:03:32
#
#-------------------------------------------------

QT += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myImap
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    TImap.cpp

HEADERS  += mainwindow.h \
    TImap.h

FORMS    += mainwindow.ui
