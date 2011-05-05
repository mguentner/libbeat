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
#ifndef SOUNDRECORDER_H
#define SOUNDRECORDER_H
#include <inttypes.h>
#include <QThread>
class SoundRecorder : public QThread
{
public:
    SoundRecorder();
    virtual ~SoundRecorder();
    virtual uint32_t get_SampleRate()=0;
    virtual void stop() = 0;
};

#endif // SOUNDRECORDER_H
