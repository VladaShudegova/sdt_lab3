#include "chartwidget.h"

ChartWidget::ChartWidget(QWidget *parent) : QWidget(parent)
{
    chartCreator = new PieChartCreator();
    chartView = new QChartView(this);
    chartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    chartView->setFixedSize(600, 400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void ChartWidget::drawChart(const QList<Record>& data)
{
    QChart* chart = chartCreator->createChart(data);
    chartView->setChart(chart);
}
