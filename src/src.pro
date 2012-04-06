TEMPLATE = lib
LANGUAGE = C++
TARGET   = beat

SOURCES += alsarecorder.cpp \
    subband.cpp \
    soundrecorder.cpp \
    soundbuffer.cpp \
    pulserecorder.cpp \
    fft.cpp \
    beatcontroller.cpp \
    beatanalyser.cpp

HEADERS += subband.h \
    soundrecorder.h \
    soundbuffer.h \
    pulserecorder.h \
    fft.h \
    beatcontroller.h \
    beatanalyser.h \
    alsarecorder.h

LIBS += -lasound -lfftw3 -lpulse-simple -lpulse
