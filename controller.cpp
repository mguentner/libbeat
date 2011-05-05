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
#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{
    myBuffer = new SoundBuffer(4096);
    myAnalyser = new BeatAnalyser(128,44100,4096);
#ifdef USE_ALSA
    dynamic_cast<AlsaRecorder*>(myRecorder);
    myRecorder = new AlsaRecorder(44100,1,myBuffer);
#endif
    myFFT = new FFT(4096);
    myFFT->setSoundBuffer(myBuffer);
    myAnalyser->setFFT(myFFT);
    m_enabled=false;
}
Controller::~Controller()
{
    delete myFFT;
    delete myRecorder;
    delete myBuffer;
    delete myAnalyser;
}
void Controller::start()
{
    if(!m_enabled)
    {
        myRecorder->start();
        //We want to process every 5 ms
        timerID = startTimer(5);
        m_enabled=true;
    }
}
void Controller::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    myFFT->process_data();
    myAnalyser->process_data();
}

void Controller::stop()
{
    if(m_enabled)
    {
        killTimer(timerID);
        myRecorder->stop();
        m_enabled=false;
    }
}
bool Controller::getEnabled()
{
    return m_enabled;
}
