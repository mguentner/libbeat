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
    testfftdisplay.cpp \
    soundbuffer.cpp \
    subband.cpp \
    beatanalyser.cpp \
    soundrecorder.cpp \
    pulserecorder.cpp \
    beatcontroller.cpp

HEADERS  += mainwindow.h \
    alsarecorder.h \
    fft.h \
    testfftdisplay.h \
    soundbuffer.h \
    subband.h \
    beatanalyser.h \
    soundrecorder.h \
    pulserecorder.h \
    beatcontroller.h

FORMS    += mainwindow.ui

LIBS += -lasound -lfftw3 -lpulse-simple -lpulse

OTHER_FILES += \
    soundanalyser.png







