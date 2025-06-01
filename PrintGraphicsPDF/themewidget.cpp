#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLegend>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtCore/QTime>
#include <QtCharts/QBarCategoryAxis>
#include <QDebug>
#include <QMenuBar>
#include <QMenu>
#include <QAction>




#include "themewidget.h"

enum ChartType {
    ChartTypeUndefined = 0,
    ChartTypeBar,
    ChartTypePie
};


ThemeWidget::ThemeWidget(QWidget *parent) :
    QWidget(parent),
    m_listCount(1),
    m_valueMax(10),
    m_valueCount(7),
    m_dataTable(generateRandomData(m_listCount,
                                     m_valueMax,
                                     m_valueCount)),
    m_chartComboBox(createChartComboBox()),
    m_colorThemeCheckBox(new QCheckBox("Черно-белый график"))
{

    connectSignals();

    // // create layout
    m_baseLayout = new QGridLayout();
    QHBoxLayout *settingsLayout = new QHBoxLayout();
    settingsLayout->addWidget(new QLabel("Выберите тип диаграммы:"));
    settingsLayout->addWidget(m_chartComboBox);
    settingsLayout->addWidget(m_colorThemeCheckBox);
    settingsLayout->addStretch();
    m_baseLayout->addLayout(settingsLayout, 0, 0);

    //create charts

    m_chartView = new QChartView(createBarChart(m_valueCount));
    m_baseLayout->addWidget(m_chartView, 1, 0);
    m_chartView->chart()->setTheme(QChart::ChartThemeBlueCerulean);
    setLayout(m_baseLayout);

    m_colorThemeCheckBox->setChecked(false);

    qgce = new QGraphicsColorizeEffect(this);
    qgce->setColor(Qt::black);
    qgce->setEnabled(false);
    m_chartView->chart()->setGraphicsEffect(qgce);

}

ThemeWidget::~ThemeWidget()
{
}

void ThemeWidget::connectSignals()
{
    connect(m_chartComboBox,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &ThemeWidget::switchChart);
    connect(m_colorThemeCheckBox, &QCheckBox::stateChanged, this, &ThemeWidget::switchColorTheme);

    //connect(this, &MainWindow::chartChanged, DR, &DR::changeChart);

}



DataTable ThemeWidget::generateRandomData(int listCount, int valueMax, int valueCount) const
{
    DataTable dataTable;

    // set seed for random stuff
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    // generate random data
    for (int i(0); i < listCount; i++) {
        DataList dataList;
        qreal yValue(0);
        for (int j(0); j < valueCount; j++) {
            yValue = yValue + (qreal)(qrand() % valueMax) / (qreal) valueCount;
            QPointF value((j + (qreal) rand() / (qreal) RAND_MAX) * ((qreal) m_valueMax / (qreal) valueCount),
                          yValue);
            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            dataList << Data(value, label);
        }
        dataTable << dataList;
    }

    return dataTable;
}

QComboBox *ThemeWidget::createChartComboBox() const
{
    // settings layout
    QComboBox *themeComboBox = new QComboBox();
    themeComboBox->addItem("BarChart", ChartType::ChartTypeBar);
    themeComboBox->addItem("PieChart", ChartType::ChartTypePie);

    return themeComboBox;
}


QChart *ThemeWidget::createBarChart(int valueCount) const
{
    Q_UNUSED(valueCount);
    QChart *chart = new QChart();
    chart->setTitle("Bar chart");

    QStackedBarSeries *series = new QStackedBarSeries(chart);
    for (int i(0); i < m_dataTable.count(); i++) {
        QBarSet *set = new QBarSet("Bar set " + QString::number(i));
        for (const Data &data : m_dataTable[i])
            *set << data.first.y();
        series->append(set);
    }
    chart->addSeries(series);
    chart->createDefaultAxes();

    return chart;
}

QChart *ThemeWidget::createPieChart() const
{
    QChart *chart = new QChart();
    chart->setTitle("Pie chart");

    qreal pieSize = 1.0 / m_dataTable.count();
    for (int i = 0; i < m_dataTable.count(); i++) {
        QPieSeries *series = new QPieSeries(chart);
        for (const Data &data : m_dataTable[i]) {
            QPieSlice *slice = series->append(data.second, data.first.y());
            if (data == m_dataTable[i].first()) {
                slice->setLabelVisible();
                slice->setExploded();
            }
        }
        qreal hPos = (pieSize / 2) + (i / (qreal) m_dataTable.count());
        series->setPieSize(pieSize);
        series->setHorizontalPosition(hPos);
        series->setVerticalPosition(0.5);
        chart->addSeries(series);
    }

    return chart;
}


void ThemeWidget::deleteChart(QChartView *oldChartView){
    m_baseLayout->removeWidget(oldChartView);
    oldChartView->deleteLater();
}

void ThemeWidget::switchChart(){
    QLayoutItem *item = m_baseLayout->itemAtPosition(1, 0);
    if (!item) return; // на всякий случай, если вдруг нет виджета

    QChartView *oldChartView = qobject_cast<QChartView*>(item->widget());
    if (!oldChartView) return;

    QChart::ChartType typeChart = static_cast<QChart::ChartType>(
        m_chartComboBox->itemData(m_chartComboBox->currentIndex()).toInt());

    deleteChart(oldChartView);

    QChartView *chartView;

    if(typeChart == ChartType::ChartTypeBar){

        chartView = new QChartView(createBarChart(m_valueCount));
    }
    else if(typeChart == ChartType::ChartTypePie){
        chartView = new QChartView(createPieChart());
        chartView->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    }

    m_baseLayout->addWidget(chartView, 1, 0);
    m_chartView = chartView;
    m_chartView->chart()->setTheme(QChart::ChartThemeBlueCerulean);
    m_chartView->chart()->setGraphicsEffect(qgce);
}

void ThemeWidget::switchColorTheme(int state)
{
    if (qgce){
        qgce->setEnabled(Qt::Checked == state);
    }
}

QChartView* ThemeWidget::getChartView() const
{
    return m_chartView;
}
