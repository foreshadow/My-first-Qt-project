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
	logindlg.cpp \
	card.cpp \
	carditem.cpp \
    universal.cpp \
    network.cpp \
    cardarray.cpp \
    gameprogress.cpp \
    cardcontainer.cpp \
    button.cpp

HEADERS  += \
    logindlg.h \
    universal.h \
    network.h \
	card.h \
	carditem.h \
    cardarray.h \
    gameprogress.h \
    cardcontainer.h \
    button.h

FORMS    += \
    logindlg.ui \
    gameprogress.ui

RESOURCES += \
    myres.qrc
