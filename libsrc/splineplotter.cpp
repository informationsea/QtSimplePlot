#include "splineplotter.h"

SPLinePlotter::SPLinePlotter(QObject *parent) : SPScatterPlotter(parent)
{

}


void SPLinePlotter::plotData(QPainter &painter, QRectF area) const
{
    QColor c(0x00, 0x66, 0xEB, static_cast<int>(0xff*m_alpha));

    painter.setPen(c);
    painter.setBrush(QBrush(c));
    for (int i = 0 ; i < m_data.length() - 1; i++) {
        painter.drawLine(translatePoint(m_data[i], area), translatePoint(m_data[i+1], area));
    }
}
