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
    SPScatterPlotterPlotInfo info(dataRange(m_data), area);

    painter.save();

    plotAxis(painter, &info, m_xlabel, m_ylable);

    painter.translate(info.plotArea.left(), info.plotArea.bottom());
    painter.scale(1, -1);

    plotGrid(painter, &info);
    plotData(painter, &info);

    painter.restore();
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


void SPScatterPlotter::plotData(QPainter &painter, const SPScatterPlotterPlotInfo *info) const
{
    QColor c(0x00, 0x66, 0xEB, 0xff*m_alpha);

    painter.setPen(c);
    painter.setBrush(QBrush(c));
    foreach (QPointF p, m_data) {
        painter.drawEllipse(QPoint((p.x()-info->plotRange.left())*info->xscale,
                                   (p.y()-info->plotRange.top())*info->yscale),
                            3, 3);
    }
}
