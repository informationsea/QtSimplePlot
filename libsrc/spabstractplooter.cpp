/*
    QtSimplePlot a library for simple plotting
    Copyright (C) 2014 Yasunobu OKAMURA

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

#include "spabstractplooter.h"

#include <math.h>
#include "simpleplotcommon.h"

SPAbstractPlooter::SPAbstractPlooter(QObject *parent) :
    QObject(parent)
{
}

qreal SPAbstractPlooter::baseUnit(qreal length)
{
#define BASE 5
    int digit = round(log10(length)/log10(BASE));
    return pow(BASE, digit-1);
}


QRectF SPAbstractPlooter::plotRange(QRectF dr, QSize standard, double bottomMargin, double margin)
{
    QRectF newrect;
    newrect.setLeft(floor(dr.left()/standard.width())*standard.width() - standard.width()*margin);
    newrect.setTop(floor(dr.top()/standard.height())*standard.height() - standard.height()*bottomMargin);
    newrect.setRight(ceil(dr.right()/standard.width())*standard.width() + standard.width()*margin);
    newrect.setBottom(ceil(dr.bottom()/standard.height())*standard.height() + standard.height()*margin);

    //qDebug() << dr.left()/standard.x() << dr.top()/standard.y() << dr.right()/standard.x() << dr.bottom()/standard.y();

    return newrect;
}

QSize SPAbstractPlooter::baseUnit(QRectF rect)
{
    return QSize(SPAbstractPlooter::baseUnit(rect.width()), SPAbstractPlooter::baseUnit(rect.height()));
}


void SPAbstractPlooter::plotAxis(QPainter &painter, const SPScatterPlotterPlotInfo *info, QString xlabel, QString ylabel) const
{
    for (int i = 0; i <=  info->plotRange.width()/info->base.width(); ++i) {
        QRectF drawRect((i-0.5)*info->base.width()*info->xscale + info->plotArea.left(),
                        info->plotArea.bottom()+4,
                        info->base.width()*info->xscale, 15);

        painter.drawText(drawRect, Qt::AlignCenter,
                         QString::number(info->plotRange.left() + i*info->base.width()));
    }

    painter.drawText(QRectF(info->plotArea.left(), info->plotArea.bottom()+20,
                            info->plotArea.width(), 15),
                     Qt::AlignCenter|Qt::AlignVCenter,
                     xlabel);


    for (int i = 0; i <=  info->plotRange.height()/info->base.height(); ++i) {
        QRectF drawRect(info->plotArea.left()-45,
                        -(i+0.5)*info->base.height()*info->yscale + info->plotArea.bottom(),
                        40, info->base.height()*info->yscale);
        painter.drawText(drawRect, Qt::AlignRight|Qt::AlignVCenter,
                         QString::number(info->plotRange.top() + i*info->base.height()));
    }

    painter.save();
    painter.rotate(-90);
    painter.drawText(QRect(-info->plotArea.bottom(), info->plotArea.left()-40,
                           info->plotArea.height(), 20),
                     Qt::AlignCenter|Qt::AlignVCenter, ylabel);
    painter.restore();
}

void SPAbstractPlooter::plotGrid(QPainter &painter, const SPScatterPlotterPlotInfo *info, double alpha) const
{
    painter.setPen(QColor(0xC4, 0xC4, 0xC4, 0xff*alpha));
    for (int i = 0; i <=  info->plotRange.width()/info->base.width(); ++i) {
        painter.drawLine(i*info->base.width()*info->xscale, 0,
                         i*info->base.width()*info->xscale, info->plotArea.height()-1);
    }
    for (int i = 0; i <=  info->plotRange.height()/info->base.height(); ++i) {
        painter.drawLine(0, i*info->base.height()*info->yscale,
                         info->plotArea.width()-1, i*info->base.height()*info->yscale);
    }
}


SPScatterPlotterPlotInfo::SPScatterPlotterPlotInfo(QRectF dr, QRect area, double bottomMargin)
{
    dataRange = dr;
    base = SPAbstractPlooter::baseUnit(dataRange);
    plotRange = SPAbstractPlooter::plotRange(dataRange, base, bottomMargin);
    plotArea = QRect(area.topLeft() + QPoint(50,10),
                     area.bottomRight() - QPoint(10, 50));
    xscale = (plotArea.width()-1)/plotRange.width();
    yscale = (plotArea.height()-1)/plotRange.height();
}
