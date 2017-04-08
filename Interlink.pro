#-------------------------------------------------
#
# Project created by QtCreator 2017-04-05T15:24:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Interlink
TEMPLATE = app

ICON = icon.icns

SOURCES += main.cpp\
        mainwindow.cpp \
    graphwindow.cpp \
    analysiswindow.cpp \
    data/protein.cpp \
    data/spectra.cpp \
    processing/pprocessor.cpp \
    processing/sprocessor.cpp

HEADERS  += mainwindow.h \
    graphwindow.h \
    analysiswindow.h \
    support/helper.h \
    support/includes.h \
    data/protein.h \
    data/spectra.h \
    support/structs.h \
    processing/pprocessor.h \
    support/constants.h \
    processing/sprocessor.h

FORMS    += mainwindow.ui \
    graphwindow.ui \
    analysiswindow.ui

RESOURCES += \
    images.qrc

DISTFILES +=

