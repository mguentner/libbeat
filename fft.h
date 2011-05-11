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
#ifndef FFT_H
#define FFT_H
#include <fftw3.h>
#include <inttypes.h>
#include <cmath>
#include "soundbuffer.h"
#define USE_HANNING
#define CLEAR_NOISE
class FFT
{
public:
    FFT(uint16_t size);
    ~FFT();
    void setSoundBuffer(SoundBuffer *value){mySoundBuffer=value;};
    void process_data();
    double get_element_r(uint16_t pos);
    double get_element_i(uint16_t pos);
    double get_magnitude(uint16_t pos);
    double get_magnitude_max();

private:
    SoundBuffer *mySoundBuffer;
    uint16_t size;
    double *input_signal;
    double *magnitude;
    double max_magnitude;
    fftw_complex *output_signal;
};

#endif // FFT_H
