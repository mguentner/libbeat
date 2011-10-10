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

namespace libbeat
{


PulseRecorder::PulseRecorder(uint32_t samplerate,uint8_t channels,SoundBuffer *mySoundBuffer,uint16_t recordsize)
{
    this->m_sampleRate=samplerate;
    this->m_SoundBuffer=mySoundBuffer;
    this->m_channels=channels;
    this->m_recordSize=recordsize;
    m_captureEnabled=false;
    m_signal = new int16_t[recordsize*channels];
}
PulseRecorder::~PulseRecorder()
{
    delete[] m_signal;
    m_captureEnabled=false;
    //Wait until run(); has finished
    wait();
}
void PulseRecorder::stop()
{
    m_captureEnabled=false;
}
bool PulseRecorder::initSound()
{
    m_ss.format= PA_SAMPLE_S16LE;
    m_ss.channels=m_channels;
    m_ss.rate=m_sampleRate;
    m_s = pa_simple_new(NULL, "libbeat",PA_STREAM_RECORD,NULL,"Sound Processing",&m_ss,NULL,NULL,NULL);
    if (m_s != NULL)
        return true; //No Error
    else
        return false; //Error
}
void PulseRecorder::closeSound()
{
    pa_simple_free(m_s);
}
void PulseRecorder::run()
{
    if(initSound())
    {
        m_captureEnabled=true;
        int error;
        while(m_captureEnabled)
        {
            if (pa_simple_read(m_s,m_signal,m_recordSize*m_channels*2,&error) < 0)
            {
                qWarning("pa_simple_read() failed: %s\n", pa_strerror(error));
                m_captureEnabled=false;
            }
            //Write data to Buffer
            for(uint16_t i=0;i<m_recordSize*m_channels;i+=m_channels)
            {
                int32_t sum=0;
                for(uint8_t j=0;j<m_channels;j++)
                    sum+=m_signal[i+j];
                m_SoundBuffer->write(i/m_channels,(int16_t)sum/m_channels);
            }
            //Emit signal and notify connected modules that new data is ready for processing
            emit newDataIsReady();
        }
    }
    m_captureEnabled=false;
    closeSound();
}
} //namespace libbeat
