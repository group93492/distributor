#-------------------------------------------------
#
# Project created by QtCreator 2012-11-17T17:37:58
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = distributor-client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    authdialog.cpp \
    protocol.cpp \
    filemanager.cpp \
    tcpclient.cpp \
    networkcfg.cpp \
    filestransferdialog.cpp

HEADERS  += mainwindow.h \
    authdialog.h \
    protocol.h \
    filemanager.h \
    tcpclient.h \
    networkcfg.h \
    filestransferdialog.h

FORMS    += mainwindow.ui \
    authdialog.ui \
    networkcfg.ui \
    filestransferdialog.ui
