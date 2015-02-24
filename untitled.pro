#-------------------------------------------------
#
# Project created by QtCreator 2015-02-12T16:53:33
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
	logindlg.cpp \
	card.cpp \
	carditem.cpp

HEADERS  += mainwindow.h \
    logindlg.h \
    universal.h \
    network.h \
	card.h \
	carditem.h

FORMS    += mainwindow.ui \
    logindlg.ui

RESOURCES += \
    myres.qrc
