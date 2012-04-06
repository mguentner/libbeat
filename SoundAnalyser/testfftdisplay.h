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
#ifndef TESTFFTDISPLAY_H
#define TESTFFTDISPLAY_H

#include <QWidget>
#include <QPainter>
#include "cmath"
#include "../src/beatcontroller.h"
class TestFFTDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit TestFFTDisplay(QWidget *parent = 0);

public slots:
    void start();
    void stop();

private:
    libbeat::BeatController *m_Controller;

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void drawNewData();
    void processSnare();
    void processDrum();
    void processCustom(QSet<uint16_t> myBeats);

};

#endif // TESTFFTDISPLAY_H
