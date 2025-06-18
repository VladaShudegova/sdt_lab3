#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QWidget>
#include <QChartView>
#include <QComboBox>
#include <QCheckBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsColorizeEffect>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>

using QtCharts::QChartView;

#include <ChartCreators/ichartcreator.h>
#include <ChartCreators/barchartcreator.h>
#include <ChartCreators/piechartcreator.h>
#include <ChartCreatorsFactory/chartcreatorsfactory.h>


#include <QPainter>
#include <QPdfWriter>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>

class ChartWidget : public QWidget
{
    Q_OBJECT
public:
    ChartWidget(shared_ptr<IChartCreatorsFactory> factory, QWidget *parent = nullptr);

private:
    shared_ptr<IChartCreatorsFactory> m_factory;
    QChartView* chartView;
    ChartType m_currentType;
    shared_ptr<QList<Record>> m_data;
    QGraphicsColorizeEffect *qgce;
    bool enableBlackAndWhite;

public slots:
    void drawChart(shared_ptr<QList<Record>> data);
    void changeChartType(int type);
    void switchColorTheme(int state);
    void printPDF();
};

#endif // CHARTWIDGET_H
