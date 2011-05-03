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
#include "soundbuffer.h"
#define DEFAULT_SAMPLERATE 44100
//How many samples we want to record with one alsa call
#define RECORD_SIZE 2048

class AlsaRecorder : public QThread
{
public:
    AlsaRecorder(uint32_t samplerate=DEFAULT_SAMPLERATE,uint8_t channels=2,SoundBuffer *mySoundBuffer=NULL);
    ~AlsaRecorder();
    uint32_t get_SampleRate(){return samplerate;};
    bool initSound();
    void closeSound();
    void process_data();
    void run();
    void stop();
signals:

public slots:

private:
    snd_pcm_t *capture_handle;
    uint32_t samplerate;
    SoundBuffer *mySoundBuffer;
    bool capture_enabled;
};

#endif // ALSARECORDER_H
