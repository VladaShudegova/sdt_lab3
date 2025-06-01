#ifndef ICHART_H
#define ICHART_H
#include <QChart>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSet>

#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QStackedBarSeries>

#include <QtCharts/QLegend>


QT_CHARTS_BEGIN_NAMESPACE
    class QChartView;
    class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

typedef QPair<QDateTime, qreal> Record;


class IChart
{
public:
    virtual ~IChart() = default;

    virtual QChart* createChart(const QList<Record>& chartData) const = 0;
};

#endif // ICHART_H
