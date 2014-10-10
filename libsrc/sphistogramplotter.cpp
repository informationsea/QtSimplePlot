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
    SPAbstractPlooter(parent), m_xlabel("X axis"), m_userInterval(0),
    m_maxvalue(1), m_minvalue(0), m_interval(0.1), m_freqmax(1)
{
}

void SPHistogramPlotter::setData(QList<qreal> data)
{
    m_data = data;
    processData();
}

void SPHistogramPlotter::setXLabel(QString xlabel)
{
    m_xlabel = xlabel;
}

void SPHistogramPlotter::plot(QPainter &painter, QRect area) const
{
    plotAxis(painter, area, m_xlabel, "Ratio");

    plotData(painter, area);
    plotGrid(painter, area, 0.6);
}

void SPHistogramPlotter::setInterval(qreal interval)
{
    m_userInterval = interval;
    processData();
}

void SPHistogramPlotter::plotData(QPainter &painter, QRectF area) const
{

    painter.setPen(Qt::black);
    painter.setBrush(QBrush(QColor(0xA5, 0xEA, 0xFF, 0xff)));
    for (int i = 0; i < m_frequency.size(); ++i) {
        QPointF lt = translatePoint(QPointF(i*m_interval + m_plotmin, 0), area);
        QPointF rb = translatePoint(QPointF((i+1)*m_interval + m_plotmin, m_frequency[i]), area);
        painter.drawRect(QRectF(lt, rb));
    }
}

void SPHistogramPlotter::processData()
{
    if (m_data.size() == 0)
        return;

    std::sort(m_data.begin(), m_data.end());
    m_maxvalue = m_data.last();
    m_minvalue = m_data.first();
    if (m_userInterval > 0) {
        m_interval = m_userInterval;
    } else {
        m_interval = SPAbstractPlooter::baseUnit(m_maxvalue - m_minvalue)/2;
    }
    m_plotmin = floor(m_minvalue/m_interval)*m_interval;
    m_plotmax = ceil(m_maxvalue/m_interval)*m_interval;
    int num = (int)((m_plotmax - m_plotmin)/m_interval);

    QList<qreal>::iterator lastit = m_data.begin();
    m_frequency.clear();
    for (int i = 1; i < num+1; ++i) {
        QList<qreal>::iterator nextit = std::upper_bound(lastit, m_data.end(), m_plotmin+i*m_interval);
        //qDebug() << i << nextit - lastit << m_plotmin+i*m_interval << m_interval;
        m_frequency << ((double)(nextit - lastit)/m_data.size());
        lastit = nextit;
    }
    m_freqmax = *std::max_element(m_frequency.begin(), m_frequency.end());
    setDataRange(QRectF(m_plotmin, 0, m_plotmax - m_plotmin, m_freqmax), true);
}
