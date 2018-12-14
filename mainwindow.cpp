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

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPointF>
#include <QList>

#include "spscatterplotter.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), scatterPlotter(this), histogramPlotter(this), linePlotter(this)
{
    ui->setupUi(this);

    QList<QPointF> data;
    data << QPointF(0, 0) << QPointF(4, 1) << QPointF(1, 0.5) << QPointF(1, 2.1) << QPointF(10,20)
         << QPointF(3.2, 5.6) << QPointF(10,0) << QPointF(0,20);
    scatterPlotter.setData(data);
    scatterPlotter.setAlpha(0.3);

    QList<QPointF> data2;
    data2 << QPointF(0, 0) << QPointF(0.1, 0.2) << QPointF(0.2, 0.3) << QPointF(0.5, 0.5) << QPointF(1.0, 1.0);
    linePlotter.setData(data2);
    linePlotter.setAlpha(0.8);

    QList<qreal> histdata;
    histdata << 0.243883553840387 << 1.02065430989971 << 0.753039337731055 << 1.51843330910103 << 0.563861162792039 << -1.70007482137525 << -0.0901433781188676 << 0.051371721669105 << 0.56077906235729 << -0.943729644464567 << 0.283605333412605 << -0.0223711340568955 << 0.395021636411691 << 0.00469873971089601 << 0.786582223247442 << -0.0642588600833232 << 0.793079937494586 << -0.70129704001095 << -1.96004597603233 << 0.775583793306135 << 1.37342703134879 << 1.4507828005012 << 0.996529563591581 << 2.85776182892291 << -2.98637518018584 << 0.236763745419266 << -0.353043810279044 << -0.0290502004804429 << 0.97719315266604 << -0.0865644087969988 << 0.3504530623374 << -0.904880178913214 << -1.73551983260597 << 0.407779867666426 << -0.691319588226962 << 0.207743057816155 << 2.70035062133663 << 0.357006167599893 << 0.172960446160705 << 1.59692780998941 << 0.990432614954554 << 0.907745132426712 << -1.43966704978468 << 0.740091019566449 << -1.59248941242519 << -0.594436313503435 << -1.92297528010262 << 0.392498393763056 << -0.0218153179311712 << -0.352961443955063 << 0.856350738347644 << -0.675161148116796 << -1.25588020558996 << -1.29960401570431 << -0.035228066785162 << 1.35733085526793 << 0.105426611427664 << 0.530881803911091 << 0.305176563189101 << -0.220873974178656 << -0.397482547570351 << 1.19027639512997 << -0.596519023406947 << 1.43575888183931 << 2.16684885874333 << 1.2399742894254 << 1.14238702768805 << 0.151510373371279 << 0.575348469161698 << 1.02491123288725 << 1.19916207325791 << -0.565665316124119 << -0.751826382377853 << -0.475574826552716 << -0.269936714455968 << 0.279951146586242 << -1.77506054781409 << 0.410547762148843 << -0.92943077769323 << 0.383550777126145 << -0.202754147560828 << 0.0922775541544295 << -1.17551074195317 << 1.4353954940002 << 0.266864797184783 << 0.91313004810137 << -1.12607855447824 << -0.896984764750198 << 0.21059045674079 << -0.357176738066895 << 1.57304980852361 << -2.50736148155507 << 0.214490643577261 << 0.0808271347423732 << -0.705550910963516 << 1.11309543991012 << -1.47486564301003 << 0.084462609111398 << 0.00584516125385771 << 0.643636182451916;
    histogramPlotter.setData(histdata);

    ui->widget->setPlotter(&scatterPlotter);
    ui->widget_2->setPlotter(&histogramPlotter);
    ui->widget_3->setPlotter(&linePlotter);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_histSpinBox_valueChanged(qreal arg1)
{
    histogramPlotter.setInterval(arg1);
    ui->widget_2->repaint();
}
