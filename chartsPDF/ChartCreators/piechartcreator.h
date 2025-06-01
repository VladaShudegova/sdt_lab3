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

    QChart* createChart(const QList<Record>& data) const override;
};

#endif // PIECHARTCREATOR_H
