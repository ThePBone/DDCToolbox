#-------------------------------------------------
#
# Project created by QtCreator 2019-09-08T00:07:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DDCToolbox
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
        addpoint.cpp \
        biquad.cpp \
        calc.cpp \
        ddccontext.cpp \
        main.cpp \
        mainwindow.cpp \
        qcustomplot.cpp \
        shiftfreq.cpp \
        textpopup.cpp \
        undocmd.cpp

HEADERS += \
        addpoint.h \
        biquad.h \
        calc.h \
        ddccontext.h \
        filtertypes.h \
        mainwindow.h \
        qcustomplot.h \
        shiftfreq.h \
        textpopup.h \
        undocmd.h \
        vdcimporter.h

FORMS += \
        addpoint.ui \
        calc.ui \
        mainwindow.ui \
        shiftfreq.ui \
        textpopup.ui

include ($$PWD/3rdparty/QSimpleUpdater/QSimpleUpdater.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc