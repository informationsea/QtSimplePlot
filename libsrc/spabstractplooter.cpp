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

#include <QDebug>
#include <math.h>
#include "simpleplotcommon.h"

SPAbstractPlooter::SPAbstractPlooter(QObject *parent) :
    QObject(parent), m_marginLeft(70), m_marginRight(20), m_marginTop(20), m_marginBottom(60)
{
}

qreal SPAbstractPlooter::baseUnit(qreal length, int base)
{
    if (length <= 0)
        return 1;
    int digit = static_cast<int>(round(log10(length)/log10(base)));
    //qDebug() << "baseUnit" << length << digit << pow(base, digit-1) << log10(length) << log10(base);
    return pow(base, digit-1);
}


void SPAbstractPlooter::setPlotRange(QRectF plotRange)
{
    m_plotRange = plotRange;
}

#define PLOT_MARGIN 0.1

void SPAbstractPlooter::setDataRange(QRectF dataRange, bool suggestParameters)
{
    m_dataRange = dataRange;
    if (!suggestParameters)
        return;

    m_plotRange = dataRange;
    m_plotRange.translate(-m_plotRange.width()*PLOT_MARGIN, -m_plotRange.height()*PLOT_MARGIN);
    m_plotRange.setWidth(m_plotRange.width()*(1+2*PLOT_MARGIN));
    m_plotRange.setHeight(m_plotRange.height()*(1+2*PLOT_MARGIN));

    setMajorTick(baseUnit(m_dataRange.width()),
                 baseUnit(m_dataRange.height()));
}

void SPAbstractPlooter::setMajorTick(qreal x, qreal y)
{
    m_majorTick = QPointF(x, y);
}


QPointF SPAbstractPlooter::translatePoint(QPointF point, QRectF plotArea) const
{
    plotArea.setLeft(plotArea.left() + m_marginLeft);
    plotArea.setRight(plotArea.right() - m_marginRight);
    plotArea.setTop(plotArea.top() + m_marginTop);
    plotArea.setBottom(plotArea.bottom() - m_marginBottom);

    QPointF scale((plotArea.width()-1)/m_plotRange.width(),
                  (plotArea.height()-1)/m_plotRange.height());
    point -= m_plotRange.topLeft();
    point.setX(point.x()*scale.x());
    point.setY(-point.y()*scale.y()-1);
    point += plotArea.bottomLeft();
    return point;
}

void SPAbstractPlooter::plotAxis(QPainter &painter, QRectF plotArea, QString xlabel, QString ylabel) const
{
    painter.setPen(Qt::black);
    painter.drawRect(QRectF(translatePoint(m_plotRange.topLeft(), plotArea),
                            translatePoint(m_plotRange.bottomRight(), plotArea)));

    int tickLeftIndex = static_cast<int>(ceil(m_plotRange.left()/m_majorTick.x()));
    int tickRightIndex = static_cast<int>(floor(m_plotRange.right()/m_majorTick.x()));

    for (int i = tickLeftIndex; i <= tickRightIndex; ++i) {
        QPointF p = translatePoint(QPointF(i*m_majorTick.x(), m_plotRange.top()), plotArea);
        painter.drawLine(p, p + QPointF(0, 5));

        // Draw tick label
        QPointF lt = translatePoint(QPointF((i-0.5)*m_majorTick.x(), m_plotRange.top()), plotArea);
        QPointF rb = translatePoint(QPointF((i+0.5)*m_majorTick.x(), m_plotRange.top()), plotArea);
        lt += QPointF(0, 10);
        rb += QPointF(0, 30);
        painter.drawText(QRectF(lt, rb), Qt::AlignCenter|Qt::AlignVCenter, QString::number(i*m_majorTick.x()));
    }

    int tickTopIndex = static_cast<int>(ceil(m_plotRange.top()/m_majorTick.y()));
    int tickBottomIndex = static_cast<int>(floor(m_plotRange.bottom()/m_majorTick.y()));

    for (int i = tickTopIndex; i <= tickBottomIndex; ++i) {
        QPointF p = translatePoint(QPointF(m_plotRange.left(), i*m_majorTick.y()), plotArea);
        painter.drawLine(p, p + QPointF(-5, 0));

        // Draw tick label
        QPointF lt = translatePoint(QPointF(m_plotRange.left(), (i-0.5)*m_majorTick.y()), plotArea);
        QPointF rb = translatePoint(QPointF(m_plotRange.left(), (i+0.5)*m_majorTick.y()), plotArea);
        lt += QPointF(-40, 0);
        rb += QPointF(-10, 0);
        painter.drawText(QRectF(lt, rb), Qt::AlignRight|Qt::AlignVCenter, QString::number(i*m_majorTick.y()));
    }

    // draw label

    {
        // Draw X label
        QPointF lt = translatePoint(QPointF(m_plotRange.left(), m_plotRange.top()), plotArea);
        QPointF rb = translatePoint(QPointF(m_plotRange.right(), m_plotRange.top()), plotArea);
        lt += QPointF(0, 30);
        rb += QPointF(0, 60);
        painter.drawText(QRectF(lt, rb), Qt::AlignCenter|Qt::AlignVCenter, xlabel);
    }

    {
        // Draw Y label
        QPointF lt = translatePoint(QPointF(m_plotRange.left(), m_plotRange.top()), plotArea);
        QPointF rb = translatePoint(QPointF(m_plotRange.left(), m_plotRange.bottom()), plotArea);
        lt += QPointF(-70, 0);
        rb += QPointF(-40, 0);

        painter.save();
        painter.rotate(-90);
        painter.drawText(QRectF(-rb.y(), lt.x(), -lt.y(), rb.x()), Qt::AlignCenter|Qt::AlignVCenter, ylabel);
        painter.restore();
    }
}

void SPAbstractPlooter::plotGrid(QPainter &painter, QRectF plotArea, double alpha) const
{
    painter.setPen(QColor(0xC4, 0xC4, 0xC4, static_cast<int>(0xff*alpha)));

    int tickLeftIndex = static_cast<int>(ceil(m_plotRange.left()/m_majorTick.x()));
    int tickRightIndex = static_cast<int>(floor(m_plotRange.right()/m_majorTick.x()));

    for (int i = tickLeftIndex; i <= tickRightIndex; ++i) {
        QPointF lt = translatePoint(QPointF((i)*m_majorTick.x(), m_plotRange.top()), plotArea);
        QPointF rb = translatePoint(QPointF((i)*m_majorTick.x(), m_plotRange.bottom()), plotArea);
        painter.drawLine(lt, rb);
    }

    int tickTopIndex = static_cast<int>(ceil(m_plotRange.top()/m_majorTick.y()));
    int tickBottomIndex = static_cast<int>(floor(m_plotRange.bottom()/m_majorTick.y()));

    for (int i = tickTopIndex; i <= tickBottomIndex; ++i) {
        QPointF lt = translatePoint(QPointF(m_plotRange.left(), (i)*m_majorTick.y()), plotArea);
        QPointF rb = translatePoint(QPointF(m_plotRange.right(), (i)*m_majorTick.y()), plotArea);
        painter.drawLine(lt, rb);
    }
}
