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

class SoundBuffer
{

public:
    SoundBuffer(uint16_t m_size=0);
    int16_t average();
    uint16_t average_pwr();
    bool write(uint16_t pos, int16_t value);
    int16_t read(uint16_t pos);

private:
    uint16_t m_size;
    QVector<int16_t> m_Buffer;

};
}
#endif // SOUNDBUFFER_H
