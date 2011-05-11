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
    myController = new Controller(0,4096);
    //Update this one every 5ms
    startTimer(25);
}

void TestFFTDisplay::paintEvent(QPaintEvent *)
{
    QPainter myPainter(this);
    myPainter.setBrush(Qt::white);
    myPainter.drawRect(QRectF(0,0,width(),height()));
    if(myController->getEnabled())
    {
        myPainter.setPen(Qt::green);
        for(uint16_t i=0;i<4096;i++)
        {
            //Draw the function itself
            myPainter.drawLine(QPoint((double)i/2048*width(),height()-myController->getFFT()->get_magnitude(i)/myController->getFFT()->get_magnitude_max()*height()),QPoint((double)i/2048*width(),width()));
        }
        uint16_t bands=myController->getAnalyser()->get_bands();
        for(uint16_t i=0;i<bands;i++)
        {
            myPainter.setPen(Qt::black);
            if(myController->getAnalyser()->get_beat(i) == true)
                myPainter.setBrush(Qt::red);
            else
                myPainter.setBrush(Qt::NoBrush);
            //Draw the beat indicator for each subband
            QRectF beatRect(QPointF((double)i/bands*width(),0),QPoint((double)(i+1)/bands*width(),0.2*height()));
            myPainter.drawRect(beatRect);
            //Set colors for detection levels
            myPainter.setBrush(Qt::magenta);
            myPainter.setPen(Qt::NoPen);
            //Draw beat detection level
            myPainter.drawRect(QRectF(QPoint((double)i/bands*width(),(height()-myController->getAnalyser()->getBand(i)->get_all_time_maximum_raw()/myController->getFFT()->get_magnitude_max()*height())),QSizeF(width()*0.005,width()*0.005)));
        }
        //Draw drum beat
        if(myController->getAnalyser()->get_drum_beat())
        {
            myPainter.setBrush(Qt::yellow);
            myPainter.drawEllipse(QPointF(width()*0.30,height()/2),width()*0.1,width()*0.1);
        }
        //Draw snare beat
        if(myController->getAnalyser()->get_snare_beat())
        {
            myPainter.setBrush(Qt::blue);
            myPainter.drawEllipse(QPointF(width()*0.70,height()/2),width()*0.1,width()*0.1);
        }
    }
}
void TestFFTDisplay::timerEvent(QTimerEvent *)
{
    update();
}

void TestFFTDisplay::start()
{
    myController->start();
}
void TestFFTDisplay::stop()
{
    myController->stop();
}
