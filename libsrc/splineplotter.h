#ifndef SPLINEPLOTTER_H
#define SPLINEPLOTTER_H

#include <QObject>
#include "spscatterplotter.h"

class SPLinePlotter : public SPScatterPlotter
{
    Q_OBJECT
public:
    explicit SPLinePlotter(QObject *parent = nullptr);

signals:

public slots:

protected:
    virtual void plotData(QPainter &painter, QRectF area) const;
};

#endif // SPLINEPLOTTER_H
