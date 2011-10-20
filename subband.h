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
#ifndef SUBBAND_H
#define SUBBAND_H
//Qt has nothing similar to <deque> so we simply use a <QList>
#include <QList>
#include <inttypes.h>

namespace libbeat
{

class SubBand
{
public:
    /*!
        @param m_size how many records SubBand needs to store (e.g. setting this to 4*samplerate/recordsize will result in 4 seconds of history)
        @param m_dropFactor (e.g. setting this to pow(0.5,(1/((double)samplerate/recordsize))) will result in 50% decrease after 2 seconds)
    */
    SubBand(uint16_t m_size=0,double m_dropFactor=0.985);
    /*!
        log a new record
        @param value the record to be logged - the oldest record will be removed
    */
    void log(double value);
    /*!
        returns the average magnitude for this SubBand
        @return the average magnitude
    */
    double average();
    /*!
        returns the highest magnitude so far. With each call the magnitude will be
        multiplied by m_dropFactor and therefore leading to a recalibration (gently reducing the magnitude)
        @return the highest magnitude so far
    */
    double getAllTimeMaximum();
    /*!
        return the highest magnitude so far without touching it. This can be used for displaying the current threshold.
        @return the highest magnitude so far
    */
    double getAllTimeMaximumRaw();
    /*!
        resets the maximum
    */
    void resetMaximum();

private:
    QList<double> m_history;
    uint16_t m_size;
    double m_allTimeMaximum;
    double m_dropFactor;
};
}
#endif // SUBBAND_H
