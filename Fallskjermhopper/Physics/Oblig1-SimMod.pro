TEMPLATE = app

QT += qml quick

SOURCES += main.cpp \
    skydiver.cpp \
    ode.cpp \
    odesolver.cpp \
    simpleprojectile.cpp \
    dragprojectile.cpp \
    windprojectile.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    skydiver.h \
    ode.h \
    odesolver.h \
    simpleprojectile.h \
    dragprojectile.h \
    windprojectile.h
