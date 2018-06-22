#-------------------------------------------------
#
# Project created by QtCreator 2018-06-10T21:31:21
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = goGame
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        difAI.cpp \
        difGame.cpp \
        goGameBase.cpp \
        goGameAIBase.cpp \
        goGamePlatform.cpp \
    window_start.cpp \
    window_select.cpp \
    window_play.cpp \
    window_tcpclient.cpp \
    window_tcpserver.cpp
HEADERS += \
        difAI.h \
        difGame.h \
        goGameBase.h \
        goGameAIBase.h \
        goGamePlatform.h \
    window_start.h \
    window_select.h \
    window_play.h \
    style.h \
    window_tcpclient.h \
    window_tcpserver.h

FORMS += \
    window_start.ui \
    window_select.ui \
    window_play.ui \
    window_tcpclient.ui \
    window_tcpserver.ui

RESOURCES += \
    mystyle.qrc

