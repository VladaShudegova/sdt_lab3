#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QWidget>
#include <QChartView>

using QtCharts::QChartView;

#include <ChartCreators/ichartcreator.h>
#include <ChartCreators/barchartcreator.h>

class ChartWidget : public QWidget
{
    Q_OBJECT
public:
    ChartWidget(QWidget *parent = nullptr);

public slots:
    void drawChart(const QList<Record>& data);

private:
    IChartCreator* chartCreator;
    QChartView* chartView;

};

#endif // CHARTWIDGET_H
