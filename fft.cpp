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
#include "fft.h"
FFT::FFT(uint16_t size=0)
{
    this->size=size;
    magnitude = new double[size/2];
    max_magnitude=0;
    /*We should use fftw_malloc instead of new since fftw_malloc aligns the memory or optimal speed*/
    output_signal = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * size);
    input_signal = new double[size];

}
FFT::~FFT()
{
    delete [] input_signal;
    delete [] magnitude;
    fftw_free(output_signal);
}
void FFT::process_data()
{
    //This has to happen prior to any initialisation of the input array
    fftw_plan plan_forward;
    plan_forward = fftw_plan_dft_r2c_1d(size, input_signal, output_signal , 0);
    //fill our array with data and apply windows if needed
#ifdef USE_BLACKMAN
    for(uint16_t i=0; i<size; i++)
    {
        double a0 = (1-0.16)/2;
        double a1 = 0.5;
        double a2 = 0.16/2;
        int16_t temp = mySoundBuffer->read(i);
        input_signal[i] = a0-a1*cos((2*M_PI*temp)/(size-1))+a2*cos((4*M_PI*temp)/(size-1));
    }
#endif
#ifdef USE_HANNING
    for(uint16_t i=0; i<size; i++)
    {
        input_signal[i] = 0.5*(1.00-cos((2*M_PI*mySoundBuffer->read(i))/(size-1)));
    }
#endif
#ifdef USE_NO_WINDOW
    for(uint16_t i=0; i<size;i++)
    {
        input_signal[i]=(double)mySoundBuffer->read(i);
    }
#endif

    fftw_execute(plan_forward);
    fftw_destroy_plan(plan_forward);
    //Calculate Magnitude
    #ifdef CLEAR_NOISE
    //We delete some values since these will ruin our output
        output_signal[0][0]=0;
        output_signal[0][1]=0;
        output_signal[1][0]=0;
        output_signal[1][1]=0;
    #endif
    for(uint16_t i=0;i<size/2;i++)
    {
        magnitude[i] = sqrt(pow(output_signal[i][0],2)+pow(output_signal[i][1],2));
        if(magnitude[i] > max_magnitude)
            max_magnitude=magnitude[i];
    }
}
double FFT::get_element_i(uint16_t pos)
{
    if(pos < size)
        return output_signal[pos][1];
    else
        return 0;
}
double FFT::get_element_r(uint16_t pos)
{
    if(pos < size)
        return output_signal[pos][0];
    else
        return 0;
}
double FFT::get_magnitude(uint16_t pos)
{
    if(pos < size/2)
        return magnitude[pos];
    else
        return 0;
}
double FFT::get_magnitude_max()
{
    return max_magnitude;
}
