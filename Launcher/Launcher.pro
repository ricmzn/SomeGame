#-------------------------------------------------
#
# Project created by QtCreator 2013-11-04T20:07:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Launcher
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += C:/MinGW/include
LIBS += C:/MinGW/lib/libglfw3.a C:/MinGW/lib/libopengl32.a C:/MinGW/lib/libgdi32.a

SOURCES += main.cpp\
        launcher.cpp

HEADERS  += launcher.h \
    videomode.h

FORMS    += launcher.ui

TRANSLATIONS += launcher_pt.ts
