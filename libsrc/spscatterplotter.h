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

#ifndef SPSCATTERPLOTTER_H
#define SPSCATTERPLOTTER_H

#include "spabstractplooter.h"
#include <QList>
#include <QPointF>
#include <QRectF>


class SPScatterPlotter : public SPAbstractPlooter
{
    Q_OBJECT
public:
    explicit SPScatterPlotter(QObject *parent = 0);

    void setData(QList<QPointF> data);
    void setXLabel(QString xlabel);
    void setYLabel(QString ylabel);
    void setAlpha(double alpha);

    virtual void plot(QPainter &painter, QRect area) const;

signals:

public slots:

private:
    QList<QPointF> m_data;
    QString m_xlabel;
    QString m_ylable;

    double m_alpha;

    static QRectF dataRange(const QList<QPointF> &data);
    void plotData(QPainter &painter, const SPScatterPlotterPlotInfo *info) const;
};

#endif // SPSCATTERPLOTTER_H
