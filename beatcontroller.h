/*
    This file is part of libbeat - a lightweight beat detection library
    Copyright (c) 2011 by Maximilian Güntner <maximilian.guentner@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef CONTROLLER_H
#define CONTROLLER_H
#define USE_PULSE

#ifdef USE_ALSA
#include "alsarecorder.h"
#endif
#ifdef USE_PULSE
#include "pulserecorder.h"
#endif
#include "fft.h"
#include "soundbuffer.h"
#include "beatanalyser.h"
#include <QObject>
#include <QTimerEvent>
class BeatController : public QObject
{
    Q_OBJECT
public:
    explicit BeatController (QObject *parent = 0,uint16_t recordsize=4096);
    ~BeatController();
    FFT* getFFT(){return myFFT;}
    BeatAnalyser* getAnalyser(){return myAnalyser;}
    SoundBuffer* getBuffer(){return myBuffer;}
    void start();
    void stop();
    bool getEnabled();

private:
    SoundRecorder *myRecorder;
    FFT *myFFT;
    SoundBuffer *myBuffer;
    BeatAnalyser *myAnalyser;
    bool m_enabled;
    int timerID;
protected:
    void timerEvent(QTimerEvent *event);

};

#endif // CONTROLLER_H
