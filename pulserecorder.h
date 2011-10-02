#ifndef PULSERECORDER_H
#define PULSERECORDER_H
#include <QThread>
#include <stdint.h>
#include "soundrecorder.h"
#include "soundbuffer.h"
#include <pulse/pulseaudio.h>
#include <pulse/simple.h>
#define DEFAULT_SAMPLERATE 44100
//How many samples we want to record with one alsa call
#define RECORD_SIZE 4096

class PulseRecorder : public SoundRecorder
{
public:
    PulseRecorder(uint32_t samplerate=DEFAULT_SAMPLERATE,uint8_t channels=2,SoundBuffer *mySoundBuffer=NULL,uint16_t recordsize=RECORD_SIZE);
    virtual ~PulseRecorder();
    uint32_t get_SampleRate(){return samplerate;}
    virtual void run();
    virtual void stop();
private:
    pa_simple *s;
    pa_sample_spec ss;
    uint16_t recordsize;
    uint32_t samplerate;
    SoundBuffer *mySoundBuffer;
    bool capture_enabled;
    uint8_t channels;
    int16_t *signal;
    bool initSound();
    void closeSound();
};

#endif // PULSERECORDER_H
