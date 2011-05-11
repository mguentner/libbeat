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
#include "alsarecorder.h"

AlsaRecorder::AlsaRecorder(uint32_t samplerate, uint8_t channels, SoundBuffer *mySoundBuffer,uint16_t recordsize)
{
    this->samplerate=samplerate;
    this->mySoundBuffer=mySoundBuffer;
    this->channels=channels;
    this->recordsize=recordsize;
    capture_enabled=false;
    signal = new int16_t[recordsize*channels];
}

AlsaRecorder::~AlsaRecorder()
{
    capture_enabled=false;
    //Wait until run(); has finished
    wait();
}
void AlsaRecorder::stop()
{
    capture_enabled=false;
}
bool AlsaRecorder::initSound()
{
    snd_pcm_hw_params_t *hw_params;
    char pcm_name[]="hw:0,0";
    int err;


    if ((err = snd_pcm_open (&capture_handle, pcm_name, SND_PCM_STREAM_CAPTURE, 0)) < 0)
    {
        qWarning("cannot open audio device (%s)\n",
                 snd_strerror (err));
        return false;
    }
    if ((err = snd_pcm_hw_params_malloc (&hw_params)) < 0)
    {
        qWarning("cannot allocate hardware parameter structure (%s)\n",
                 snd_strerror (err));
        return false;
    }
    if ((err = snd_pcm_hw_params_any (capture_handle, hw_params)) < 0)
    {
        qWarning("cannot initialize hardware parameter structure (%s)\n",
                 snd_strerror (err));
        return false;
    }
    if ((err = snd_pcm_hw_params_set_access (capture_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0)
    {
        qWarning("cannot set access type (%s)\n",
                 snd_strerror (err));
        return false;
    }
    if ((err = snd_pcm_hw_params_set_format (capture_handle, hw_params, SND_PCM_FORMAT_S16_LE)) < 0)
    {
        qWarning("cannot set sample format (%s)\n",
                 snd_strerror (err));
        return false;
    }
    if ((err = snd_pcm_hw_params_set_rate_near (capture_handle, hw_params, (unsigned int *) &samplerate, 0)) < 0)
    {
        qWarning("cannot set sample rate (%s)\n",
                 snd_strerror (err));
        return false;
    }
    if ((err = snd_pcm_hw_params_set_channels (capture_handle, hw_params, channels)) < 0)
    {
        qWarning("cannot set channel count (%s)\n",
                 snd_strerror (err));
        return false;
    }
    if ((err = snd_pcm_hw_params (capture_handle, hw_params)) < 0)
    {
        qWarning("cannot set parameters (%s)\n",
                 snd_strerror (err));
        return false;
    }
    snd_pcm_hw_params_free (hw_params);
    return true;
}
void AlsaRecorder::closeSound()
{
    snd_pcm_close (capture_handle);
}
void AlsaRecorder::run()
{
    int err;
    //stop will set this to false
    capture_enabled=true;
    if(initSound())
    {
        while(capture_enabled)
        {
            if ((err = snd_pcm_readi (capture_handle, signal, recordsize)) != recordsize)
            {
                if ((err = snd_pcm_prepare (capture_handle)) < 0)
                {
                    qWarning("cannot prepare audio interface for use (%s)\n",
                             snd_strerror (err));

                }
            }
            //Write data to Buffer
            for(uint16_t i=0;i<recordsize*channels;i+=channels)
            {
                uint32_t sum=0;
                for(uint8_t j=0;j<channels;j++)
                    sum+=signal[i+j];
                mySoundBuffer->write(i/channels,(int16_t)sum/channels);
            }
        }
    }
    closeSound();
}
