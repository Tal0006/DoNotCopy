QT       += core gui
QT += network
QT += core
QT += sql
QT += httpserver

QT -= gui
QT += axcontainer
QT += multimedia multimediawidgets

QT += core gui widgets network

TARGET = network
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS




TARGET = HttpGetExample
CONFIG   += console
CONFIG   -= app_bundle



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    course.cpp \
    lecturer.cpp \
    main.cpp \
    mainwindow.cpp \
    student.cpp

HEADERS += \
    course.h \
    lecturer.h \
    mainwindow.h \
    student.h


FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pol.qrc \
    res.qrc \
    res.qrc

