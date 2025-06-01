#include "piechartcreator.h"


PieChartCreator::PieChartCreator() {}


struct MonthAverageValue
{
    qreal sum   = 0.0;
    int   count = 0;
};



QChart* PieChartCreator::createChart(const QList<Record>& chartData) const
{
    if (chartData.isEmpty())
        return nullptr;


    QList<Record> data = chartData;
    std::sort(data.begin(), data.end(),
              [](const Record &a, const Record &b) { return a.first < b.first; });


    QMap<QString, MonthAverageValue> monthlyData;

    for (const Record &rec : std::as_const(data))
    {
        const QString monthKey = rec.first.toString("MM-yyyy");
        monthlyData[monthKey].sum   += rec.second;
        monthlyData[monthKey].count += 1;
    }


    QtCharts::QPieSeries *series = new QtCharts::QPieSeries;

    int ordinalMonth = 1;      //  «1, 2, 3…» вместо "01-2023"

    for (auto it = monthlyData.cbegin(); it != monthlyData.cend(); ++it)
    {
        const double average = it.value().sum / it.value().count;
        series->append(QString::number(ordinalMonth), average);
        ++ordinalMonth;
    }

    /*  Показать подписи прямо на секторах  */
    series->setLabelsVisible(true);
    series->setLabelsPosition(QtCharts::QPieSlice::LabelInsideHorizontal);


    QChart *chart = new QChart;
    chart->addSeries(series);
    chart->setTitle(QStringLiteral("Средние значения по месяцам (PieChart)"));
    chart->legend()->setAlignment(Qt::AlignRight);

    return chart;
}
