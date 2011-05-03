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
#ifndef BEATANALYSER_H
#define BEATANALYSER_H
#include <QVector>
#include <QDebug>
#include "subband.h"
#include "inttypes.h"
#include "fft.h"
#include "alsarecorder.h"
class BeatAnalyser
{
public:
    BeatAnalyser(uint16_t num_bands,uint32_t samplerate, uint16_t recordsize);
    ~BeatAnalyser();
    void setFFT(FFT *value){myFFT=value;};
    void process_data();
    uint16_t get_bands(){return num_bands;};
    /*get beats with their corresponding frequency*/
    bool get_beat(uint16_t pos);
    //TODO: get_beat with frequency - BeatAnalyser will then return the right subband
    bool get_beat_frequency(uint32_t frequency);
    /*get beats associated with instruments*/
    bool get_drum_beat();
    bool get_snare_beat();

private:
    uint16_t num_bands;
    uint32_t samplerate;
    uint16_t recordsize;
    FFT *myFFT;
    QVector<SubBand*> *mySubBands;
    QVector<bool> *myBeats;
};

#endif // BEATANALYSER_H
