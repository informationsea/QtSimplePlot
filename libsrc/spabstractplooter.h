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

#ifndef SPABSTRACTPLOOTER_H
#define SPABSTRACTPLOOTER_H

#include <QObject>
#include <QPainter>

class SPScatterPlotterPlotInfo {
public:
    qreal xscale;
    qreal yscale;
    QRectF dataRange;
    QRectF plotRange;
    QRect plotArea;
    QSizeF base;

    SPScatterPlotterPlotInfo(QRectF dataRange, QRect area, double bottomMargin = 1, double baseWidthScale = 1);
};

class SPAbstractPlooter : public QObject
{
    Q_OBJECT
public:
    explicit SPAbstractPlooter(QObject *parent = 0);

    virtual void plot(QPainter &painter, QRect area) const = 0;

    static qreal baseUnit(qreal length, int base = 5);
    static QSizeF baseUnit(QRectF rect);
    static QRectF plotRange(QRectF dataRange, QSizeF standard, double bottomMargin = 1, double margin = 1);

protected:
    void plotAxis(QPainter &painter, const SPScatterPlotterPlotInfo *info, QString xlabel, QString ylabel) const;
    void plotGrid(QPainter &painter, const SPScatterPlotterPlotInfo *info, double alpha = 1) const;

signals:

public slots:

};

#endif // SPABSTRACTPLOOTER_H
