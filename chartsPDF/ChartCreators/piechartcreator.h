#ifndef PIECHARTCREATOR_H
#define PIECHARTCREATOR_H

#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCore>

#include "ichartcreator.h"

class PieChartCreator : public IChartCreator
{
public:
    PieChartCreator();

    QChart* createChart(shared_ptr<QList<Record>> data) const override;
};

#endif // PIECHARTCREATOR_H
