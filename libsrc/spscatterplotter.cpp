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

#include "spscatterplotter.h"

#include <QPainter>
#include <QPaintEvent>
#include <QDebug>

#include <math.h>
#include "simpleplotcommon.h"

SPScatterPlotter::SPScatterPlotter(QObject *parent) :
    SPAbstractPlooter(parent), m_xlabel("X axis"), m_ylable("Y axis"), m_alpha(1)
{

}

void SPScatterPlotter::setData(QList<QPointF> data)
{
    m_data = data;
    setDataRange(dataRange(data), true);
}

void SPScatterPlotter::setXLabel(QString xlabel)
{
    m_xlabel = xlabel;
}

void SPScatterPlotter::setYLabel(QString ylabel)
{
    m_ylable = ylabel;
}

void SPScatterPlotter::setAlpha(double alpha)
{
    m_alpha = alpha;
}

void SPScatterPlotter::plot(QPainter &painter, QRect area) const
{
    plotGrid(painter, area);
    plotAxis(painter, area, m_xlabel, m_ylable);
    plotData(painter, area);
}

QRectF SPScatterPlotter::dataRange(const QList<QPointF> &data)
{
    QRectF range(0, 0, 1, 1);
    if (data.size() == 0)
        return range;
    range.setCoords(data[0].x(), data[0].y(), data[0].x(), data[0].y());
    foreach (QPointF p, data) {
        range.setCoords(MIN(p.x(), range.left()),
                        MIN(p.y(), range.top()),
                        MAX(p.x(), range.right()),
                        MAX(p.y(), range.bottom()));
    }
    return range;
}


void SPScatterPlotter::plotData(QPainter &painter, QRectF area) const
{
    QColor c(0x00, 0x66, 0xEB, static_cast<int>(0xff*m_alpha));

    painter.setPen(c);
    painter.setBrush(QBrush(c));
    foreach (QPointF p, m_data) {
        painter.drawEllipse(translatePoint(p, area),
                            3, 3);
    }
}
