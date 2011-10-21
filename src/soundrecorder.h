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
#ifndef SOUNDRECORDER_H
#define SOUNDRECORDER_H
#include <inttypes.h>
#include <QThread>

namespace libbeat
{
/*!
  abstract SoundRecorder
*/
class SoundRecorder : public QThread
{
    Q_OBJECT

public:
    SoundRecorder();
    virtual ~SoundRecorder();
    virtual void stop() = 0;

signals:
    /*!
        This signal needs to be emitted once all samples have been recorded. The BeatController will connect to this signal and then trigger the Analyser
    */
    void newDataIsReady();

};
}
#endif // SOUNDRECORDER_H
