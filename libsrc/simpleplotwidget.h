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

#ifndef SIMPLEPLOTWIDGET_H
#define SIMPLEPLOTWIDGET_H

#include <QWidget>
#include "spabstractplooter.h"

class SimplePlotWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SimplePlotWidget(QWidget *parent = nullptr);

    void setPlotter(const SPAbstractPlooter *plotter);

protected:
    void paintEvent(QPaintEvent * event);

signals:

public slots:

private:
    const SPAbstractPlooter *m_plotter;

};

#endif // SIMPLEPLOTWIDGET_H
