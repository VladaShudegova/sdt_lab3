#include "barchartcreator.h"

BarChartCreator::BarChartCreator() {}

struct MonthAverageValue
{
    qreal sum = 0.0;
    int count = 0;
};

QChart* BarChartCreator::createChart(shared_ptr<QList<Record>> chartData) const
{
    shared_ptr<QList<Record>> data = make_shared<QList<Record>>(*chartData);

    QMap<QString, MonthAverageValue> monthlyData;

    std::sort(data->begin(), data->end(), [](const Record&a, const Record& b){ return a.first < b.first;});

    QBarSet* barSet = new QBarSet(data->at(0).first.toString("yyyy"));
    //QDateTime nextMonth = data->at(0).first.addMonths(1);
    QStringList months;

    for(int i = 0; i < data->size(); i++)
    {
        QString date = data->at(i).first.toString("MM-yyyy");
        monthlyData[date].sum += data->at(i).second;
        monthlyData[date].count += 1;
    }

    int monthNumber = 1;
    for(const auto &key: monthlyData.keys())
    {
        months << QString::number(monthNumber);
        monthNumber++;
        *barSet << monthlyData[key].sum/monthlyData[key].count;
    }


    QBarSeries* series = new QBarSeries();
    series->append(barSet);

    QChart* chart = new QChart();
    chart->addSeries(series);

    QBarCategoryAxis* monthsAxis = new QBarCategoryAxis();
    monthsAxis->append(months);

    QValueAxis* valueAxis = new QValueAxis();

    chart->addAxis(monthsAxis, Qt::AlignBottom);
    chart->addAxis(valueAxis, Qt::AlignLeft);
    series->attachAxis(monthsAxis);
    series->attachAxis(valueAxis);

    return chart;
}
