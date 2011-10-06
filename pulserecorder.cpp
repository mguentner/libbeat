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
#include "pulserecorder.h"

PulseRecorder::PulseRecorder(uint32_t samplerate,uint8_t channels,SoundBuffer *mySoundBuffer,uint16_t recordsize)
{
    this->samplerate=samplerate;
    this->mySoundBuffer=mySoundBuffer;
    this->channels=channels;
    this->recordsize=recordsize;
    capture_enabled=false;
    signal = new int16_t[recordsize*channels];
}
PulseRecorder::~PulseRecorder()
{
    delete[] signal;
    capture_enabled=false;
    //Wait until run(); has finished
    wait();
}
void PulseRecorder::stop()
{
    capture_enabled=false;
}
bool PulseRecorder::initSound()
{
    ss.format= PA_SAMPLE_S16LE;
    ss.channels=channels;
    ss.rate=samplerate;
    s = pa_simple_new(NULL, "libbeat",PA_STREAM_RECORD,NULL,"Sound Processing",&ss,NULL,NULL,NULL);
    if (s != NULL)
        return true; //No Error
    else
        return false; //Error
}
void PulseRecorder::closeSound()
{
    pa_simple_free(s);
}
void PulseRecorder::run()
{
    if(initSound())
    {
        capture_enabled=true;
        int error;
        while(capture_enabled)
        {
            if (pa_simple_read(s,signal,recordsize*channels*2,&error) < 0)
            {
                qWarning("pa_simple_read() failed: %s\n", pa_strerror(error));
                capture_enabled=false;
            }
            //Write data to Buffer
            for(uint16_t i=0;i<recordsize*channels;i+=channels)
            {
                int32_t sum=0;
                for(uint8_t j=0;j<channels;j++)
                    sum+=signal[i+j];
                mySoundBuffer->write(i/channels,(int16_t)sum/channels);
            }
            //Emit signal and notify connected modules that new data is ready for processing
            emit newDataIsReady();
        }
    }
    capture_enabled=false;
    closeSound();
}
