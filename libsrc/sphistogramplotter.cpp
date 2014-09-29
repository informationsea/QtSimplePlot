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

#include "sphistogramplotter.h"

#include <QDebug>
#include <algorithm>
#include <math.h>
#include "simpleplotcommon.h"

SPHistogramPlotter::SPHistogramPlotter(QObject *parent) :
    SPAbstractPlooter(parent), m_xlabel("X axis"), m_maxvalue(1), m_minvalue(0), m_interval(0.1), m_freqmax(1)
{
}

void SPHistogramPlotter::setData(QList<qreal> data)
{
    m_data = data;

    if (m_data.size() == 0)
        return;

    std::sort(m_data.begin(), m_data.end());
    m_maxvalue = m_data.last();
    m_minvalue = m_data.first();
    m_interval = SPAbstractPlooter::baseUnit(m_maxvalue - m_minvalue);
    m_plotmin = floor(m_minvalue/m_interval)*m_interval;
    m_plotmax = ceil(m_maxvalue/m_interval)*m_interval;
    int num = (int)((m_plotmax - m_plotmin)/m_interval);

    QList<qreal>::iterator lastit = m_data.begin();
    m_frequency.clear();
    for (int i = 1; i < num+1; ++i) {
        QList<qreal>::iterator nextit = std::upper_bound(lastit, m_data.end(), m_plotmin+i*m_interval);
        //qDebug() << i << nextit - lastit << m_plotmin+i*m_interval << m_interval;
        m_frequency << nextit - lastit;
        lastit = nextit;
    }
    m_freqmax = *std::max_element(m_frequency.begin(), m_frequency.end());
    //qDebug() << m_frequency << m_freqmax;
}

void SPHistogramPlotter::setXLabel(QString xlabel)
{
    m_xlabel = xlabel;
}

void SPHistogramPlotter::plot(QPainter &painter, QRect area) const
{
    SPScatterPlotterPlotInfo info(QRectF(m_plotmin, 0, m_maxvalue - m_minvalue, m_freqmax), area, 0);
    //info.plotRange.setBottom(0);
    plotAxis(painter, &info, m_xlabel, "Count");

    painter.save();
    painter.translate(info.plotArea.left(), info.plotArea.bottom());
    painter.scale(1, -1);

    plotData(painter, &info);
    plotGrid(painter, &info, 0.6);

    painter.restore();
}

void SPHistogramPlotter::plotData(QPainter &painter, const SPScatterPlotterPlotInfo *info) const
{
    painter.setPen(Qt::blue);
    painter.setBrush(QBrush(Qt::blue));
    //qDebug() << m_frequency << m_frequency.size();
    for (int i = 0; i < m_frequency.size(); ++i) {
        painter.drawRect(QRectF((i*m_interval - info->plotRange.left() + m_plotmin)*info->xscale, 0,
                                m_interval*info->xscale, m_frequency[i]*info->yscale));
    }
}
