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

namespace libbeat
{

SoundBuffer::SoundBuffer(uint16_t size)
{
    this->m_size=size;
    m_Buffer.resize(size);
}

int16_t SoundBuffer::average()
{
    int32_t sum=0;
    for(uint16_t i=0;i<m_size;i++)
    {
        sum+=m_Buffer[i];
    }
    sum/=m_size;
    return (int16_t)sum;
}
uint16_t SoundBuffer::average_pwr()
{
    uint32_t sum=0;
    for(uint16_t i=0;i<m_size;i++)
    {
        if(m_Buffer[i] < 0)
            sum+=-1*m_Buffer[i];
        else
            sum+=m_Buffer[i];
    }
    sum/=m_size;
    return (uint16_t)sum;
}
bool SoundBuffer::write(uint16_t pos,int16_t value)
{
        if(pos < m_size)
        {
            m_Buffer[pos]=value;
            return true;
        }
        else
            return false;
}
int16_t SoundBuffer::read(uint16_t pos)
{
        return m_Buffer.at(pos);
}
} //namespace libbeat
