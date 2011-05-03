#-------------------------------------------------
#
# Project created by QtCreator 2011-04-27T10:08:17
#
#-------------------------------------------------

QT       += core gui

TARGET = SoundAnalyser
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    alsarecorder.cpp \
    fft.cpp \
    controller.cpp \
    testfftdisplay.cpp \
    soundbuffer.cpp \
    subband.cpp \
    beatanalyser.cpp

HEADERS  += mainwindow.h \
    alsarecorder.h \
    fft.h \
    controller.h \
    testfftdisplay.h \
    soundbuffer.h \
    subband.h \
    beatanalyser.h

FORMS    += mainwindow.ui

LIBS += -lasound -lfftw3
