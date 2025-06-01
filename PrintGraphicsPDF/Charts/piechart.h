#ifndef PIECHART_H
#define PIECHART_H
#include "ichart.h"

class PieChart : public IChart
{
public:
    PieChart();
    virtual QChart* createChart(const QList<Record>& chartData) const;
};

#endif // PIECHART_H
