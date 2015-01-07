#-------------------------------------------------
#
# Project created by QtCreator 2014-12-14T01:48:25
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BezierSurfaces
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cpwidget.cpp \
    bezierwidget.cpp

HEADERS  += mainwindow.h \
    cpwidget.h \
    bezierwidget.h \
    commons.h

FORMS    += mainwindow.ui

OTHER_FILES +=

RESOURCES += \
    resources.qrc
