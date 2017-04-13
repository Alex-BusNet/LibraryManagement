#-------------------------------------------------
#
# Project created by QtCreator 2017-03-22T10:31:55
#
#-------------------------------------------------

QT       += core gui concurrent
QMAKE_CXXFLAGS += -std=c++0x

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LibraryManagement
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    user.cpp \
    staff.cpp \
    librarydb.cpp \
    userbase.cpp \
    useroptions.cpp \
    editbook.cpp \
    edituser.cpp

HEADERS  += mainwindow.h \
    user.h \
    datatypes.h \
    staff.h \
    librarydb.h \
    manager.h \
    userbase.h \
    useroptions.h \
    editbook.h \
    edituser.h

FORMS    += mainwindow.ui \
    useroptions.ui \
    editbook.ui \
    edituser.ui
