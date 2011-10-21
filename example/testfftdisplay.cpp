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
#include "testfftdisplay.h"
TestFFTDisplay::TestFFTDisplay(QWidget *parent) :
    QWidget(parent)
{
    m_Controller = new libbeat::BeatController(0,4096,44100,192);
    //Setup two test frequencies: 600Hz and 12000Hz
    m_Controller->addCustomBeat(600);
    m_Controller->addCustomBeat(12000);
    //Draw when processed and analysed data is ready to be displayed
    connect(m_Controller,SIGNAL(processingDone()),this,SLOT(drawNewData()));
    //Connect some test slots to the Controller's signals
    connect(m_Controller,SIGNAL(beatDrum()),this,SLOT(processDrum()));
    connect(m_Controller,SIGNAL(beatSnare()),this,SLOT(processSnare()));
    connect(m_Controller,SIGNAL(beatCustom(QSet<uint16_t>)),this,SLOT(processCustom(QSet<uint16_t>)));
}

void TestFFTDisplay::paintEvent(QPaintEvent *)
{
    QPainter myPainter(this);
    myPainter.setBrush(Qt::white);
    myPainter.drawRect(QRectF(0,0,width(),height()));
    if(m_Controller->getEnabled())
    {
        myPainter.setPen(Qt::green);
        for(uint16_t i=0;i<4096;i++)
        {
            //Draw the function itself
            myPainter.drawLine(QPoint((double)i/2048*width(),height()-m_Controller->getFFT()->get_magnitude(i)/m_Controller->getFFT()->get_magnitude_max()*height()),QPoint((double)i/2048*width(),width()));
        }
        uint16_t bands=m_Controller->getAnalyser()->getBands();
        for(uint16_t i=0;i<bands;i++)
        {
            myPainter.setPen(Qt::black);
            if(m_Controller->getAnalyser()->getBeat(i) == true)
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
            myPainter.drawRect(QRectF(QPoint((double)i/bands*width(),(height()-m_Controller->getAnalyser()->getBand(i)->getAllTimeMaximumRaw()/m_Controller->getFFT()->get_magnitude_max()*height())),QSizeF(width()*0.005,width()*0.005)));
        }
        //Draw drum beat
        if(m_Controller->getAnalyser()->getDrumBeat())
        {
            myPainter.setBrush(Qt::yellow);
            myPainter.drawEllipse(QPointF(width()*0.30,height()/2),width()*0.1,width()*0.1);
        }
        //Draw snare beat
        if(m_Controller->getAnalyser()->getSnareBeat())
        {
            myPainter.setBrush(Qt::blue);
            myPainter.drawEllipse(QPointF(width()*0.70,height()/2),width()*0.1,width()*0.1);
        }
        //Draw volume frame
        myPainter.setBrush(Qt::NoBrush);
        myPainter.setPen(Qt::black);
        myPainter.drawRect(QRectF(0.89*width(), 0.92*height(), 0.07*width(), -0.52*height()));
        //Draw volume
        myPainter.setBrush(Qt::green);
        myPainter.setPen(Qt::black);
        myPainter.drawRect(QRectF(0.90*width(), 0.90*height(), 0.05*width(), (log(m_Controller->getBuffer()->average_pwr())/log(65536))*-0.50*height()));
    }
}
void TestFFTDisplay::drawNewData()
{
    update();
}

void TestFFTDisplay::start()
{
    m_Controller->start();
}
void TestFFTDisplay::stop()
{
    m_Controller->stop();
}
void TestFFTDisplay::processDrum()
{
    qDebug("Drum beat.\n");
}
void TestFFTDisplay::processSnare()
{
    qDebug("Snare beat.\n");
}
void TestFFTDisplay::processCustom(QSet<uint16_t> myBeats)
{
    QSetIterator<uint16_t> i(myBeats);
    while (i.hasNext())
    {
            qDebug("Custom beat at %d Hz\n",i.next());
    }
}
