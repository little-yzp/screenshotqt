#-------------------------------------------------
#
# Project created by QtCreator 2024-12-30T19:49:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = screenshot
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

CONFIG += c++11

SOURCES += \
        main.cpp \
    snipasteapp.cpp \
    picview.cpp \
    transparentmask.cpp \
    shape.cpp \
    util.cpp \
    textshowdialog.cpp

HEADERS += \
    snipasteapp.h \
    picview.h \
    transparentmask.h\
    shortcutfilter.h \
    shape.h \
    Ocrlib/include/*.h \
    util.h \
    textshowdialog.h


FORMS += \
    picview.ui \
    transparentmask.ui \
    textshowdialog.ui

# LIBS += $$PWD/lib/vld.lib
LIBS += Ocrlib/lib/RapidOcrOnnx.lib

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icon.qrc

RC_ICONS = icon\screenshot.ico

TRANSLATIONS = app_zh_CN.ts

release{
    DEFINES += QT_NO_DEBUG_OUTPUT
}
