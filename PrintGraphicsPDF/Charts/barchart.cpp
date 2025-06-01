#include "barchart.h"



BarChart::BarChart() {}

QChart* BarChart::createChart(const QList<Record>& chartData) const
{
    QList<Record> data = chartData;

    std::sort(data.begin(), data.end(), [](const Record&a, const Record& b){ return a.first < b.first;});

    QBarSet* barSet = new QBarSet(data[0].first.toString("MM YYYY"));
    QDateTime nextMonth = data[0].first.addMonths(1);
    QStringList months;

    for(int i = 0; i < data.size(); i++)
    {
        months << QString::number(i+1);
        int count = 0;
        qreal sum = 0;
        for(; i < data.size() && data[i].first < nextMonth; i++)
        {
            count++;
            sum += data[i].second;
        }

        *barSet << sum/count;
        nextMonth = nextMonth.addMonths(1);
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
