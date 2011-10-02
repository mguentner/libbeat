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

SubBand::SubBand(uint16_t size)
{
    this->size=size;
    all_time_maximum=0;
}
void SubBand::log(double value)
{
    if(value > all_time_maximum)
        all_time_maximum=value;
     //Log our new value
     myHistory.prepend(value);
     //Delete the oldest record
     if(myHistory.size() > size)
         myHistory.removeLast();
     //else: We are still filling our list. this should only happend during the first second of recording
}
double SubBand::average()
{
     double sum=0;
     foreach (const double &entry, myHistory)
          sum+=entry;
     return sum/myHistory.size();
}
double SubBand::get_all_time_maximum()
{
    //With every call of this method we gradually lower the maximum to quickly adapt to changes in the input
    all_time_maximum*=0.9998;
    return all_time_maximum;
}
double SubBand::get_all_time_maximum_raw()
{
    //This function is for display purpuse only. No recalibration will be performed
    return all_time_maximum;
}
void SubBand::reset_maximum()
{
    all_time_maximum=0;
}
