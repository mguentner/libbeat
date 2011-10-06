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
#ifndef ALSARECORDER_H
#define ALSARECORDER_H

#include <QThread>
#include <alsa/asoundlib.h>
#include <error.h>
#include <stdint.h>
#include "soundrecorder.h"
#include "soundbuffer.h"


class AlsaRecorder : public SoundRecorder
{
    Q_OBJECT

public:
    AlsaRecorder(uint32_t samplerate,uint8_t channels,SoundBuffer *mySoundBuffer,uint16_t recordsize);
    virtual ~AlsaRecorder();
    uint32_t get_SampleRate(){return samplerate;}
    virtual void run();
    virtual void stop();
//Variables
private:
    snd_pcm_t *capture_handle;
    uint16_t recordsize;
    uint32_t samplerate;
    SoundBuffer *mySoundBuffer;
    bool capture_enabled;
    uint8_t channels;
    int16_t *signal;
//Methods
private:
    bool initSound();
    void closeSound();
};

#endif // ALSARECORDER_H
