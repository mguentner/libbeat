/*
    This file is part of libbeat - a lightweight beat detection library
    Copyright (C) 2011 <maximilian.guentner@gmail.com>

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
#ifndef ALSARECORDER_H
#define ALSARECORDER_H

#include <QThread>
#include <alsa/asoundlib.h>
#include <error.h>
#include <inttypes.h>
#include "soundrecorder.h"
#include "soundbuffer.h"
#define DEFAULT_SAMPLERATE 44100
//How many samples we want to record with one alsa call
#define RECORD_SIZE 4096

class AlsaRecorder : public SoundRecorder
{
public:
    AlsaRecorder(uint32_t samplerate=DEFAULT_SAMPLERATE,uint8_t channels=2,SoundBuffer *mySoundBuffer=NULL,uint16_t recordsize=4096);
    virtual ~AlsaRecorder();
    uint32_t get_SampleRate(){return samplerate;};
    bool initSound();
    void closeSound();
    virtual void run();
    virtual void stop();
signals:

public slots:

private:
    snd_pcm_t *capture_handle;
    uint16_t recordsize;
    uint32_t samplerate;
    SoundBuffer *mySoundBuffer;
    bool capture_enabled;
    uint8_t channels;
    int16_t *signal;

};

#endif // ALSARECORDER_H
