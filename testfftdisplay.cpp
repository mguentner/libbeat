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
#include "testfftdisplay.h"
TestFFTDisplay::TestFFTDisplay(QWidget *parent) :
    QWidget(parent)
{
    //Update this one every 5ms
    startTimer(5);
}

void TestFFTDisplay::paintEvent(QPaintEvent *)
{
    QPainter myPainter(this);
    myPainter.setBrush(Qt::white);
    myPainter.drawRect(QRectF(0,0,width(),height()));
    if(myController.getEnabled())
    {
        myPainter.setPen(Qt::green);
        for(uint16_t i=0;i<1024;i++)
        {
            myPainter.drawLine(QPoint((double)i/1024*width(),height()-myController.getFFT()->get_magnitude(i)/myController.getFFT()->get_magnitude_max()*height()),QPoint((double)i/1024*width(),width()));
        }
        //Display beats
        uint16_t bands=myController.getAnalyser()->get_bands();
        for(uint16_t i=0;i<bands;i++)
        {
            if(myController.getAnalyser()->get_beat(i) == true)
                myPainter.setBrush(Qt::red);
            else
                myPainter.setBrush(Qt::NoBrush);
            QRectF beatRect(QPointF((double)i/bands*width(),0),QPoint((double)(i+1)/bands*width(),0.2*height()));
            myPainter.drawRect(beatRect);
        }
        //Draw drum beat:
        if(myController.getAnalyser()->get_drum_beat())
        {
            myPainter.setBrush(Qt::yellow);
            myPainter.drawEllipse(QPoint(width()*0.30,height()/2),width()*0.1,width()*0.1);
        }
        if(myController.getAnalyser()->get_snare_beat())
        {
            myPainter.setBrush(Qt::blue);
            myPainter.drawEllipse(QPoint(width()*0.70,height()/2),width()*0.1,width()*0.1);
        }
    }
}
void TestFFTDisplay::timerEvent(QTimerEvent *)
{
    update();
}

void TestFFTDisplay::start()
{
    myController.start();
}
void TestFFTDisplay::stop()
{
    myController.stop();
}
