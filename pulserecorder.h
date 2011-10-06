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
#ifndef PULSERECORDER_H
#define PULSERECORDER_H
#include <QThread>
#include <stdint.h>
#include "soundrecorder.h"
#include "soundbuffer.h"
#include <pulse/pulseaudio.h>
#include <pulse/simple.h>

class PulseRecorder : public SoundRecorder
{
    Q_OBJECT

public:
    PulseRecorder(uint32_t samplerate,uint8_t channels,SoundBuffer *mySoundBuffer,uint16_t recordsize);
    virtual ~PulseRecorder();
    uint32_t get_SampleRate(){return samplerate;}
    virtual void run();
    virtual void stop();
//Variables
private:
    pa_simple *s;
    pa_sample_spec ss;
    SoundBuffer *mySoundBuffer;
    int16_t *signal;
    uint16_t recordsize;
    uint32_t samplerate;
    bool capture_enabled;
    uint8_t channels;
//Methods
private:
    bool initSound();
    void closeSound();
};

#endif // PULSERECORDER_H
