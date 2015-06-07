#-------------------------------------------------
#
# Project created by QtCreator 2014-08-09T13:58:52
#
#-------------------------------------------------

QT += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DaysLeft
TEMPLATE = app

SOURCES += src/main.cpp\
    src/MainWindow.cpp \
    src/DLEvent.cpp \
    src/DLView.cpp \
    src/DLModel.cpp \
    src/DLDelegate.cpp

HEADERS  += src/MainWindow.h \
    src/DLEvent.h \
    src/DLView.h \
    src/DLModel.h \
    src/DLDelegate.h \
    src/constants.h

RESOURCES += \
    resources.qrc
