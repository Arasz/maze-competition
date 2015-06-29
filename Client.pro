#-------------------------------------------------
#
# Project created by QtCreator 2015-05-10T11:07:04
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app
CONFIG   += c++14


QMAKE_CXXFLAGS += -std=c++14


SOURCES += main.cpp\
        mainwindow.cpp \
    Robot.cpp \
    WorldMap.cpp \
    BreadthFirstSearch.cpp \
    RobotState.cpp \
    SearchState.cpp \
    SearchProblem.cpp \
    SearchPath.cpp

HEADERS  += mainwindow.h \
    Types.h \
    Robot.h \
    WorldMap.h \
    SearchProblem.h \
    BreadthFirstSearch.h \
    RobotState.h \
    SearchState.h \
    SearchPath.h


FORMS    += mainwindow.ui
