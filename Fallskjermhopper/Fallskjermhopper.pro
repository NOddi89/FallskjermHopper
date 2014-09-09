#-------------------------------------------------
#
# Project created by QtCreator 2014-09-02T20:05:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Fallskjermhopper
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    Physics/dragprojectile.cpp \
    Physics/ode.cpp \
    Physics/odesolver.cpp \
    Physics/simpleprojectile.cpp \
    Physics/windprojectile.cpp \
    skydiver.cpp \
    skydiverode.cpp

HEADERS  += dialog.h \
    Physics/dragprojectile.h \
    Physics/ode.h \
    Physics/odesolver.h \
    Physics/simpleprojectile.h \
    Physics/windprojectile.h \
    skydiver.h \
    skydiverode.h

FORMS    += dialog.ui

RESOURCES += \
    fallskjermhopper.qrc



