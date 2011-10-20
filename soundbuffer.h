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
#ifndef SOUNDBUFFER_H
#define SOUNDBUFFER_H
#include <inttypes.h>
#include <QVector>

namespace libbeat
{
/*!
    Simple storage class for signed 16-bit samples
*/
class SoundBuffer
{

public:
    /*!
        @param m_size how many samples SoundBuffer should store
    */
    SoundBuffer(uint16_t m_size=0);
    /*! returns the average value of the SoundBuffer
        @return average value
    */
    int16_t average();
    /*! returns the average power of the SoundBuffer (e.g the volume)
        @return average power
    */
    uint16_t average_pwr();
    /*!
        write value to pos
        @param value the value
        @param pos the position
        @return true if successful, false if not
    */
    bool write(uint16_t pos, int16_t value);
    /*!
        get a certain positon
        @param pos the position
        @return the value at pos
    */
    int16_t read(uint16_t pos);

private:
    uint16_t m_size;
    QVector<int16_t> m_Buffer;

};
}
#endif // SOUNDBUFFER_H
