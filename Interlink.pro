#-------------------------------------------------
#
# Project created by QtCreator 2017-04-05T15:24:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Interlink++
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

ICON = icon.icns

SOURCES += main.cpp\
        mainwindow.cpp \
    graphwindow.cpp \
    analysiswindow.cpp \
    data/protein.cpp \
    data/spectra.cpp \
    processing/pprocessor.cpp \
    processing/sprocessor.cpp \
    tablecell.cpp

HEADERS  += mainwindow.h \
    graphwindow.h \
    analysiswindow.h \
    data/protein.h \
    data/spectra.h \
    processing/pprocessor.h \
    processing/sprocessor.h \
    support/includes+structs.h \
    tablecell.h

FORMS  += mainwindow.ui \
    graphwindow.ui \
    analysiswindow.ui \
    tablecell.ui

RESOURCES += \
    images.qrc

DISTFILES +=

macx {
    LIBS += -L"/usr/local/Cellar/boost/1.65.1/lib"
    INCLUDEPATH += "/usr/local/Cellar/boost/1.65.1/include"

    ICON = Icon.icns
    IFILE = $$OUT_PWD/Interlink++.app/Contents/Info.plist
    copyinfo.commands = $(COPY_FILE) $$PWD/Info.plist $$IFILE
    first.depends = $(first) copyinfo
    export(first.depends)
    export(copyinfo.commands)
    QMAKE_EXTRA_TARGETS += first copyinfo
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.10
    QMAKE_POST_LINK += "/Users/Venky/Qt/5.10.1/clang_64/bin/macdeployqt Interlink++.app -no-strip"
    QMAKE_LFLAGS += -Bstatic
}



