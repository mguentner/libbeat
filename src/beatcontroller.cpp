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
#include "beatcontroller.h"

namespace libbeat
{

BeatController::BeatController(QObject *parent, uint16_t recordSize, uint32_t sampleRate, uint16_t m_bandCount) : QObject(parent)
{
    m_Buffer = new SoundBuffer(recordSize);
    m_Analyser = new BeatAnalyser(m_bandCount,sampleRate,recordSize);
#ifdef USE_ALSA
    dynamic_cast<AlsaRecorder*>(myRecorder);
    myRecorder = new AlsaRecorder(sampleRate,2,myBuffer,recordSize);
#endif
#ifdef USE_PULSE
    dynamic_cast<PulseRecorder*>(m_Recorder);
    m_Recorder = new PulseRecorder(sampleRate,2,m_Buffer,recordSize);
#endif
    m_FFT = new FFT(recordSize);
    m_FFT->setSoundBuffer(m_Buffer);
    m_Analyser->setFFT(m_FFT);
    m_enabled=false;
}
BeatController::~BeatController()
{
    delete m_FFT;
    delete m_Recorder;
    delete m_Buffer;
    delete m_Analyser;
}
void BeatController::start()
{
    if(!m_enabled)
    {
        m_Recorder->start();
        m_enabled=true;
        //Connect SoundRecorder::newDataIsReady to processNewData()
        connect(m_Recorder,SIGNAL(newDataIsReady()),this, SLOT(processNewData()));
    }
}

void BeatController::stop()
{
    if(m_enabled)
    {
        m_Recorder->stop();
        m_enabled=false;
    }
}
bool BeatController::getEnabled()
{
    return m_enabled;
}

void BeatController::processNewData()
{
    if(m_enabled)
    {
        m_FFT->process_data();
        m_Analyser->processData();
        emit processingDone();
        if(m_Analyser->getDrumBeat())
            emit beatDrum();
        if(m_Analyser->getSnareBeat())
            emit beatSnare();
        //Check for a beat for every frequency in our list
        QSet<uint16_t> myBeats;
        QSetIterator<uint16_t> i(m_customBeats);
        while(i.hasNext())
        {
            if(m_Analyser->getBeatFrequency(i.peekNext()))
                myBeats.insert(i.peekNext());
            i.next();
        }
        if(!myBeats.empty())
            emit beatCustom(myBeats);
    }
}
} //namespace libbeat
