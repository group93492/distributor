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
        GUI/mainwindow.cpp \
    GUI/authdialog.cpp \
    Core/protocol.cpp \
    GUI/filemanager.cpp \
    Core/tcpclient.cpp \
    GUI/filestransferdialog.cpp \
    Core/filehandlers.cpp \
    GUI/networkcfgdialog.cpp

HEADERS  += GUI/mainwindow.h \
    GUI/authdialog.h \
    Core/protocol.h \
    GUI/filemanager.h \
    Core/tcpclient.h \
    GUI/filestransferdialog.h \
    Core/filehandlers.h \
    GUI/networkcfgdialog.h

FORMS    += GUI/mainwindow.ui \
    GUI/authdialog.ui \
    GUI/filestransferdialog.ui \
    GUI/networkcfgdialog.ui
