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
#include <QSet>

namespace libbeat
{

class BeatController : public QObject
{
    Q_OBJECT
public:
    explicit BeatController (QObject *parent = 0,uint16_t recordsize=4096);
    ~BeatController();
    FFT* getFFT(){return m_FFT;}
    BeatAnalyser* getAnalyser(){return m_Analyser;}
    SoundBuffer* getBuffer(){return m_Buffer;}
    void start();
    void stop();
    bool getEnabled();
    void addCustomBeat(uint16_t value){m_customBeats.insert(value);}
    void removeCustomBeat(uint16_t value){m_customBeats.remove(value);}
private:
    SoundRecorder *m_Recorder;
    FFT *m_FFT;
    SoundBuffer *m_Buffer;
    BeatAnalyser *m_Analyser;
    bool m_enabled;
    QSet<uint16_t> m_customBeats;

private slots:
    void processNewData();

signals:
    void processingDone();
    void beatDrum();
    void beatSnare();
    void beatCustom(QSet<uint16_t> beats);

};
}
#endif // CONTROLLER_H
