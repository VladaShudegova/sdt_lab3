#ifndef BARCHARTCREATOR_H
#define BARCHARTCREATOR_H

#include <QtAlgorithms>
#include <QBarSet>
#include <QBarSeries>
#include <QBarCategoryAxis>
#include <QValueAxis>

using QtCharts::QBarSet;
using QtCharts::QBarSeries;
using QtCharts::QBarCategoryAxis;
using QtCharts::QValueAxis;

#include "ichartcreator.h"


class BarChartCreator : public IChartCreator
{
public:
    BarChartCreator();

    QChart* createChart(shared_ptr<QList<Record>> data) const override;
};

#endif // BARCHARTCREATOR_H
