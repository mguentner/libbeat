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
#include "beatanalyser.h"

BeatAnalyser::BeatAnalyser(uint16_t num_bands, uint32_t samplerate, uint16_t recordsize)
{
    this->num_bands=num_bands;
    this->samplerate=samplerate;
    this->recordsize=recordsize;
    mySubBands = new QVector<SubBand*>;
    for(uint16_t i=0;i<num_bands;i++)
    {
        SubBand *tmp = new SubBand(samplerate/recordsize);
        mySubBands->append(tmp);
    }
    myBeats = new QVector<bool> (num_bands,false);
}
BeatAnalyser::~BeatAnalyser()
{
    delete mySubBands;
    delete myBeats;
}
void BeatAnalyser::process_data()
{
    uint16_t freq_per_band=recordsize/2/num_bands;
    myBeats->fill(false);
    for(uint16_t i=0;i<num_bands;i++)
    {
        double sum=0;
        for(uint16_t j=0;j<freq_per_band;j++)
        {
            sum+=myFFT->get_magnitude(i*freq_per_band+j);
        }
        sum/=freq_per_band;
        mySubBands->at(i)->log(sum);
        if(mySubBands->at(i)->average() < sum && mySubBands->at(i)->get_all_time_maximum()*0.8 < sum)
        {
            myBeats->replace(i,true);
            //qDebug() << sum;
        }
    }
}
bool BeatAnalyser::get_beat(uint16_t pos)
{
    if(pos < num_bands)
        return myBeats->at(pos);
    else
        return false;
}
bool BeatAnalyser::get_beat_frequency(uint32_t frequency)
{
    uint16_t freq_per_band=samplerate/num_bands/2;
    return myBeats->at((int)frequency/freq_per_band);
}
bool BeatAnalyser::get_drum_beat()
{
    /*We want to detect beats from 50Hz up to 200Hz*/
    bool tmp=false;
    uint16_t freq_per_band=samplerate/num_bands/2;
    uint32_t low_limit=50/freq_per_band;
    uint32_t high_limit=200/freq_per_band;
    for(uint16_t i=low_limit;i<high_limit;i++)
        tmp |= myBeats->at(i);
    return tmp;
}
bool BeatAnalyser::get_snare_beat()
{
    /*We want to detect beats from 1500Hz up to 2500Hz - this of course will return a beat more often due to the broad spectrum*/
    bool tmp=false;
    uint16_t freq_per_band=samplerate/num_bands/2;
    uint32_t low_limit=1500/freq_per_band;
    uint32_t high_limit=2000/freq_per_band;
    for(uint16_t i=low_limit;i<high_limit;i++)
        tmp |= myBeats->at(i);
    return tmp;
}
SubBand* BeatAnalyser::getBand(uint16_t value)
{
    if(value < num_bands)
        return mySubBands->at(value);
}
