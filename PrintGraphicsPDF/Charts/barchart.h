#ifndef BARCHART_H
#define BARCHART_H

#include "ichart.h"

class BarChart : public IChart
{
public:
    BarChart();
    QChart* createChart(const QList<Record>& chartData) const;
};

#endif // BARCHART_H
