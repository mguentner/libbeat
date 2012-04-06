#-------------------------------------------------
#
# Project created by QtCreator 2011-04-27T10:08:17
#
#-------------------------------------------------

QT       += core gui

TARGET = SoundAnalyser
TEMPLATE = app
DEPENDPATH  += ../src
INCLUDEPATH += ../src

SOURCES += main.cpp\
           mainwindow.cpp \
           testfftdisplay.cpp


HEADERS += mainwindow.h \
    testfftdisplay.h \
    subband.h \
    soundrecorder.h \
    soundbuffer.h \
    pulserecorder.h \
    fft.h \
    beatcontroller.h \
    beatanalyser.h \
    alsarecorder.h

FORMS += mainwindow.ui

LIBS += -L../src/ -lbeat

OTHER_FILES += \
    soundanalyser.png










