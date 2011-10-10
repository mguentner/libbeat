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
#include "subband.h"

namespace libbeat
{

SubBand::SubBand(uint16_t size,double dropFactor)
{
    this->size=size;
    this->dropFactor=dropFactor;
    allTimeMaximum=0;
}
void SubBand::log(double value)
{
    if(value > allTimeMaximum)
        allTimeMaximum=value;
     //Log our new value
     m_history.prepend(value);
     //Delete the oldest record
     if(m_history.size() > size)
         m_history.removeLast();
     //else: We are still filling our list. this should only happend during the first second of recording
}
double SubBand::average()
{
     double sum=0;
     foreach (const double &entry, m_history)
          sum+=entry;
     return sum/m_history.size();
}
double SubBand::getAllTimeMaximum()
{
    //With every call of this method we gradually lower the maximum to quickly adapt to changes in the input
    allTimeMaximum*=dropFactor;
    return allTimeMaximum;
}
double SubBand::getAllTimeMaximumRaw()
{
    //This function is for display purpose only. No recalibration will be performed
    return allTimeMaximum;
}
void SubBand::resetMaximum()
{
    allTimeMaximum=0;
}
} //libbeat
