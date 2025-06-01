#ifndef ICHARTCREATOR_H
#define ICHARTCREATOR_H

#include <QChart>
#include <memory>

using QtCharts::QChart;
using std::shared_ptr;
using std::make_shared;

#include "ChartData/chartdata.h"

class IChartCreator
{
public:
    virtual QChart* createChart(const QList<Record>& data) const = 0;
};

#endif // ICHARTCREATOR_H
