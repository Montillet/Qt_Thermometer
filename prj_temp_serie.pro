#-------------------------------------------------
#
# Project created by QtCreator 2013-07-08T11:31:34
#
#-------------------------------------------------

QT       += core gui
CONFIG      += qwt

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = prj_temp_serie
TEMPLATE = app

INCLUDEPATH += C:\qwt-6.1.0   #\include
DEPENDPATH += C:\qwt-6.1.0\lib

LIBS += -LC:\qwt-6.1.0\lib



SOURCES += main.cpp\
        mainwindow.cpp \
    rs232.cpp

HEADERS  += mainwindow.h \
    rs232.h

FORMS    += mainwindow.ui
