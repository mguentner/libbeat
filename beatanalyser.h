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
#ifndef BEATANALYSER_H
#define BEATANALYSER_H
#include <QVector>
#include <QDebug>
#include "subband.h"
#include "inttypes.h"
#include "fft.h"
#include "alsarecorder.h"

namespace libbeat
{

class BeatAnalyser
{
public:
    BeatAnalyser(uint16_t m_bandCount,uint32_t m_sampleRate, uint16_t m_recordSize);
    ~BeatAnalyser();
    void setFFT(FFT *value){m_FFT=value;}
    void processData();
    uint16_t getBands(){return m_bandCount;}
    // get beats with their corresponding frequency
    bool getBeat(uint16_t pos);
    // get_beat with frequency
    bool getBeatFrequency(uint32_t frequency);
    // get beats associated with instruments
    bool getDrumBeat();
    bool getSnareBeat();
    SubBand* getBand(uint16_t value);

private:
    uint16_t m_bandCount;
    uint32_t m_sampleRate;
    uint16_t m_recordSize;
    FFT *m_FFT;
    QVector<SubBand*> *m_SubBands;
    QVector<bool> *m_beats;
};
}
#endif // BEATANALYSER_H
