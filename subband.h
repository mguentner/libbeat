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
/*This class will store samplerate/recordsize values to provide 1 second (*) of magnitudes for each subband

  exmaple: for 44100Hz and 2048 samples recordsize we need to store 21 values.

  (*) This however can be changed which will then increase/decrease the sensitivity of the beatfinding algorithm*/

class SubBand
{
public:
    SubBand(uint16_t size=0);
    void log(double value);
    double average();
    double get_all_time_maximum();
    double get_all_time_maximum_raw();

    void reset_maximum();
private:
    QList<double> myHistory;
    uint16_t size;
    double all_time_maximum;
};

#endif // SUBBAND_H
