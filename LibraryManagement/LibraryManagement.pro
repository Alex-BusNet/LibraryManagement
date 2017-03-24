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
    librarydb.cpp \
    manager.cpp \
    userbase.cpp \
    userwindow.cpp \
    assistantwindow.cpp \
    managerwindow.cpp \
    addnewuser.cpp

HEADERS  += mainwindow.h \
    user.h \
    datatypes.h \
    staff.h \
    librarydb.h \
    manager.h \
    userbase.h \
    userwindow.h \
    assistantwindow.h \
    managerwindow.h \
    addnewuser.h

FORMS    += mainwindow.ui \
    userwindow.ui \
    assistantwindow.ui \
    managerwindow.ui \
    addnewuser.ui
