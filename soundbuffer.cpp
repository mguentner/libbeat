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
#include "soundbuffer.h"

SoundBuffer::SoundBuffer(uint16_t size)
{
    this->size=size;
    myBuffer.resize(size);
}

int16_t SoundBuffer::average()
{
    int32_t sum=0;
    for(uint16_t i=0;i<size;i++)
    {
        sum+=myBuffer[i];
    }
    sum/=size;
    return (int16_t)sum;
}
uint16_t SoundBuffer::average_pwr()
{
    uint32_t sum=0;
    for(uint16_t i=0;i<size;i++)
    {
        if(myBuffer[i] < 0)
            sum+=-1*myBuffer[i];
        else
            sum+=myBuffer[i];
    }
    sum/=size;
    return (uint16_t)sum;
}
bool SoundBuffer::write(uint16_t pos,int16_t value)
{
        if(pos < size)
        {
            myBuffer[pos]=value;
            return true;
        }
        else
            return false;
}
int16_t SoundBuffer::read(uint16_t pos)
{
        return myBuffer.at(pos);
}
