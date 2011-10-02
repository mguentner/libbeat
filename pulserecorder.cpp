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
    ss.format= PA_SAMPLE_S16NE;
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
    capture_enabled=true;
    if(initSound())
    {
        int error;
        while(capture_enabled)
        {
            if (pa_simple_read(s,signal,recordsize,&error) < 0)
            {
                qWarning("pa_simple_read() failed: %s\n", pa_strerror(error));
                capture_enabled=false;
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
