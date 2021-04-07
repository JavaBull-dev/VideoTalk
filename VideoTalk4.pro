#-------------------------------------------------
#
# Project created by QtCreator 2021-01-29T14:38:53
#
#-------------------------------------------------

QT       += core gui multimedia concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoTalk4
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
# DEFINES += QT_NO_DEBUG_OUTPUT ，禁止qDebug()输出
# 添加后，清理项目，重新构建项目
DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_NO_DEBUG_OUTPUT

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    serversetdialog.cpp \
    openglwidget.cpp \
    iffmpeg.cpp \
    iffmpegaudio.cpp \
    ffmpegvideo.cpp \
    collectionsetdialog.cpp \
    avinputstream.cpp \
    avoutputstream.cpp \
    customeevent.cpp \
    logdialog.cpp \
    closewaitdialog.cpp \
    callaccpetdialog.cpp

HEADERS += \
        mainwindow.h \
    serversetdialog.h \
    openglwidget.h \
    iffmpeg.h \
    iffmpegaudio.h \
    ffmpegvideo.h \
    collectionsetdialog.h \
    avinputstream.h \
    avoutputstream.h \
    customeevent.h \
    logdialog.h \
    closewaitdialog.h \
    callaccpetdialog.h

FORMS += \
        mainwindow.ui \
    serversetdialog.ui \
    collectionsetdialog.ui \
    logdialog.ui \
    closewaitdialog.ui \
    callaccpetdialog.ui

INCLUDEPATH += F:/BaiDuDownload/ffmpeg-N-100471-gbff6fbead8-win64-gpl-shared/include
LIBS  +=-LF:/BaiDuDownload/ffmpeg-N-100471-gbff6fbead8-win64-gpl-shared/lib
LIBS  += -lavcodec -lavformat -lswscale -lavutil -lswresample -lavfilter -lavdevice

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
