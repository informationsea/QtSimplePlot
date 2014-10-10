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

class SPAbstractPlooter : public QObject
{
    Q_OBJECT
public:
    explicit SPAbstractPlooter(QObject *parent = 0);

    virtual void plot(QPainter &painter, QRect area) const = 0;
    static qreal baseUnit(qreal length, int base = 5);

    QRectF plotRange() const {return m_plotRange;}
    QRectF dataRange() const {return m_dataRange;}
    QPointF majorTick() const {return m_majorTick;}

    void setPlotRange(QRectF plotRange);
    void setDataRange(QRectF dataRange, bool suggestParameters);
    void setMajorTick(qreal x, qreal y);

protected:
    QPointF translatePoint(QPointF point, QRectF plotArea) const;

    void plotAxis(QPainter &painter, QRectF plotArea, QString xlabel, QString ylabel) const;
    void plotGrid(QPainter &painter, QRectF plotArea, double alpha = 1) const;

private:
    QRectF m_plotRange;
    QRectF m_dataRange;
    //QRectF m_plotArea;
    QPointF m_majorTick;
    //QPointF m_scale;

    qreal m_marginLeft;
    qreal m_marginRight;
    qreal m_marginTop;
    qreal m_marginBottom;

signals:

public slots:

};

#endif // SPABSTRACTPLOOTER_H
