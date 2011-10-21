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
    testfftdisplay.cpp \
    ../src/alsarecorder.cpp \
    ../src/subband.cpp \
    ../src/soundrecorder.cpp \
    ../src/soundbuffer.cpp \
    ../src/pulserecorder.cpp \
    ../src/fft.cpp \
    ../src/beatcontroller.cpp \
    ../src/beatanalyser.cpp

HEADERS  += mainwindow.h \
    testfftdisplay.h \
    ../src/subband.h \
    ../src/soundrecorder.h \
    ../src/soundbuffer.h \
    ../src/pulserecorder.h \
    ../src/fft.h \
    ../src/beatcontroller.h \
    ../src/beatanalyser.h \
    ../src/alsarecorder.h

FORMS    += mainwindow.ui

LIBS += -lasound -lfftw3 -lpulse-simple -lpulse

OTHER_FILES += \
    soundanalyser.png










