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
    data/protein.h \
    data/spectra.h \
    processing/pprocessor.h \
    processing/sprocessor.h \
    support/includes+structs.h

FORMS    += mainwindow.ui \
    graphwindow.ui \
    analysiswindow.ui

RESOURCES += \
    images.qrc

DISTFILES +=

macx {
    IFILE = $$OUT_PWD/Interlink.app/Contents/Info.plist
    copyinfo.commands = $(COPY_FILE) $$PWD/Info.plist $$IFILE
}


LIBS += -L"/usr/local/Cellar/boost/1.65.1/lib"
INCLUDEPATH += "/usr/local/Cellar/boost/1.65.1/include"
