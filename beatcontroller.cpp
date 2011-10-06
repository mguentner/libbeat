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

BeatController::BeatController(QObject *parent,uint16_t recordsize) : QObject(parent)
{
    myBuffer = new SoundBuffer(recordsize);
    myAnalyser = new BeatAnalyser(192,44100,recordsize);
#ifdef USE_ALSA
    dynamic_cast<AlsaRecorder*>(myRecorder);
    myRecorder = new AlsaRecorder(44100,2,myBuffer,recordsize);
#endif
#ifdef USE_PULSE
    dynamic_cast<PulseRecorder*>(myRecorder);
    myRecorder = new PulseRecorder(44100,2,myBuffer,recordsize);
#endif
    myFFT = new FFT(recordsize);
    myFFT->setSoundBuffer(myBuffer);
    myAnalyser->setFFT(myFFT);
    m_enabled=false;
}
BeatController::~BeatController()
{
    delete myFFT;
    delete myRecorder;
    delete myBuffer;
    delete myAnalyser;
}
void BeatController::start()
{
    if(!m_enabled)
    {
        myRecorder->start();
        m_enabled=true;
        //Connect SoundRecorder::newDataIsReady to processNewData()
        connect(myRecorder,SIGNAL(newDataIsReady()),this, SLOT(processNewData()));
    }
}

void BeatController::stop()
{
    if(m_enabled)
    {
        myRecorder->stop();
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
        myFFT->process_data();
        myAnalyser->process_data();
        emit processingDone();
    }
}
