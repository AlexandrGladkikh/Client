#-------------------------------------------------
#
# Project created by QtCreator 2015-03-05T11:18:23
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += release

TARGET = client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    including/chatengine.cpp \
    including/smiledialog.cpp \
    including/smileitem.cpp \
    including/smiletable.cpp \
    including/textedit.cpp \
    including/userlist.cpp \
    including/useritem.cpp \
    including/setsetting.cpp

HEADERS  += mainwindow.h \
    including/chatengine.h \
    including/smiledialog.h \
    including/smileitem.h \
    including/smiletable.h \
    including/textedit.h \
    including/userlist.h \
    including/ui_mainwindow.h \
    including/userdata.h \
    including/useritem.h \
    including/setsetting.h

FORMS    += including/mainwindow.ui

RESOURCES += \
    Smile.qrc
