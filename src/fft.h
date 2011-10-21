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
#ifndef FFT_H
#define FFT_H
#include <fftw3.h>
#include <inttypes.h>
#include <cmath>
#include "soundbuffer.h"
/*! \def USE_NO_WINDOW
    no window ( http://en.wikipedia.org/wiki/Window_function ) will be used when filling the input array
*/

/*! \def USE_BLACKMAN
    the Blackman window will be used when filling the input array ( http://en.wikipedia.org/wiki/Window_function#Blackman_windows )
*/

/*! \def USE_HANNING
    the Hanning window will be used when filling the input array ( http://en.wikipedia.org/wiki/Window_function#Hann_window )
*/

#define USE_NO_WINDOW

/*! \def CLEAR_NOISE
    the FFT results can be misleading for the frequency band 0-30Hz) - this define will just set this to 0
*/
#define CLEAR_NOISE

namespace libbeat
{

class FFT
{
public:
    /*!
        creates a FFT of a certain size
        @param m_size
    */
    FFT(uint16_t m_size);
    ~FFT();
    /*!
        sets the address of m_SoundBuffer
        @param *value
    */
    void setSoundBuffer(SoundBuffer *value){m_SoundBuffer=value;}
    /*!
        starts processing of new data if m_SoundBuffer is not NULL
    */
    void process_data();
    /*!
        provides access to the real part of the processed signal
        @param pos the position in the FFT, valid input is 0-(m_size-1)
        @return the value at the position. if the position is out of range, return will be 0
    */
    double get_element_r(uint16_t pos);
    /*!
        provides access to the imaginary part of the processed signal
        @param pos the processed signal at pos, valid input is 0-(m_size-1)
        @return the value at pos. if pos is out of range, return will be 0
    */
    double get_element_i(uint16_t pos);
    /*!
        provides access to the magnitude of the signal
        @param pos the processed signal at pos, valid input is 0-(m_size/2)
        @return the value at the pos. if pos is out of range, return will be 0
    */
    double get_magnitude(uint16_t pos);
    /*!
        provides the highest magnitude of the whole signal. This can be used for scaling graphs
        @return highest magnitude
    */
    double get_magnitude_max();

private:
    /*! the SoundBuffer from where FFT gets new data */
    SoundBuffer *m_SoundBuffer;
    /*! the size of the input signal */
    uint16_t m_size;
    /*! the input signal */
    double *m_inputSignal;
    /*! an array where the magnitude will be stored */
    double *m_magnitude;
    /*! the maximum magnitude inside m_magnitude */
    double m_maxMagnitude;
    /*! the results of fftw */
    fftw_complex *m_outputSignal;
};
}

#endif // FFT_H
