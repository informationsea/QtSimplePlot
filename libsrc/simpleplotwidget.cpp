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

#include "simpleplotwidget.h"

#include <QDebug>

SimplePlotWidget::SimplePlotWidget(QWidget *parent) :
    QWidget(parent), m_plotter(0)
{
}

void SimplePlotWidget::setPlotter(const SPAbstractPlooter *plotter)
{
    m_plotter = plotter;
}

void SimplePlotWidget::paintEvent(QPaintEvent */*event*/)
{
    if (m_plotter == 0)
        return;
    QPainter p(this);

    QRect area(0, 0, width(), height());
    p.fillRect(area, QBrush(Qt::white));
    //qDebug() << area;
    m_plotter->plot(p, area);
}
