#ifndef THEMEWIDGET_H
#define THEMEWIDGET_H

#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>
#include <QGraphicsColorizeEffect>
#include <QColorDialog>
#include <QColor>
#include <QPainter>
#include <QPdfWriter>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
    class QComboBox;
    class QCheckBox;
    class QPushButton;
    class QGridLayout;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
    class QChartView;
    class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

    typedef QPair<QPointF, QString> Data;
    typedef QList<Data> DataList;
    typedef QList<DataList> DataTable;

class WidgetChart:public QWidget
{
    Q_OBJECT
public:
    explicit WidgetChart(QWidget *parent = nullptr);
    ~WidgetChart(){}
};


class ThemeWidget: public QWidget
{    Q_OBJECT
public:
    explicit ThemeWidget(QWidget *parent = nullptr);
    ~ThemeWidget();

private Q_SLOTS:
    void switchColorTheme(int state);
    void switchChart();
    void printPDF();

private:
    DataTable generateRandomData(int listCount, int valueMax, int valueCount) const;
    QComboBox *createChartComboBox() const;
    void connectSignals();
    void deleteChart(QChartView*);

public:
    QChart *createBarChart(int valueCount) const;
    QChart *createPieChart() const;


private:
    int m_listCount;
    int m_valueMax;
    int m_valueCount;

    QChartView* m_chartView;
    DataTable m_dataTable;
    QComboBox *m_chartComboBox;
    QCheckBox *m_colorThemeCheckBox;
    QPushButton *m_printButton;
    QGridLayout *m_baseLayout;
    QGraphicsColorizeEffect *qgce;
};

#endif // THEMEWIDGET_H
