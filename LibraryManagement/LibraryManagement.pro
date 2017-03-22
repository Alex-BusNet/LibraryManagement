#-------------------------------------------------
#
# Project created by QtCreator 2017-03-22T10:31:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LibraryManagement
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    user.cpp \
    staff.cpp \
    assistant.cpp \
    librarydb.cpp \
    manager.cpp \
    userbase.cpp

HEADERS  += mainwindow.h \
    user.h \
    datatypes.h \
    staff.h \
    assistant.h \
    librarydb.h \
    manager.h \
    userbase.h

FORMS    += mainwindow.ui
