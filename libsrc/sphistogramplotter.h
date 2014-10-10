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

#ifndef SPHISTOGRAMPLOTTER_H
#define SPHISTOGRAMPLOTTER_H

#include "spabstractplooter.h"

#include <QList>

class SPHistogramPlotter : public SPAbstractPlooter
{
    Q_OBJECT
public:
    explicit SPHistogramPlotter(QObject *parent = 0);

    void setData(QList<qreal> data);
    void setXLabel(QString xlabel);

    virtual void plot(QPainter &painter, QRect area) const;

    void setNumberOfBins(int num);
    qreal plotMinimumValue() const {return m_plotmin;}
    qreal plotMaximumValue() const {return m_plotmax;}
    qreal plotInterval() const {return m_interval;}

signals:

public slots:

private:
    void plotData(QPainter &painter, const SPScatterPlotterPlotInfo *info) const;
    void processData();

    QString m_xlabel;
    QList<qreal> m_data;
    QList<qreal> m_frequency;

    int m_numberofbins;

    qreal m_maxvalue;
    qreal m_minvalue;
    qreal m_interval;
    qreal m_plotmin;
    qreal m_plotmax;
    qreal m_freqmax;
};

#endif // SPHISTOGRAMPLOTTER_H
