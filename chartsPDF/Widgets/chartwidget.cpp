#include "chartwidget.h"

ChartWidget::ChartWidget(shared_ptr<ChartCreatorsFactory> factory, QWidget *parent) : QWidget(parent)
{
    m_factory = factory;
    chartView = new QChartView(this);
    chartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);



    QComboBox* chartTypeComboBox = new QComboBox();
    chartTypeComboBox->addItem("BarChart", static_cast<int>(ChartType::Bar));
    chartTypeComboBox->addItem("PieChart", static_cast<int>(ChartType::Pie));
    chartTypeComboBox->setCurrentIndex(0);
    m_currentType = static_cast<ChartType>(chartTypeComboBox->currentIndex());
    //chartCreator = m_factory->getCreator(m_currentType);

    QCheckBox* checkBoxBW = new QCheckBox("Черно-белый график");
    checkBoxBW->setChecked(false);

    QHBoxLayout* settingsLayout = new QHBoxLayout();
    settingsLayout->addWidget(new QLabel("Выберите тип диаграммы:"));
    settingsLayout->addWidget(chartTypeComboBox);
    settingsLayout->addWidget(checkBoxBW);
    settingsLayout->addStretch();

    settingsLayout->setAlignment(Qt::AlignTop);


    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addLayout(settingsLayout);
    layout->addWidget(chartView);
    layout->setStretchFactor(chartView, 1);

    qgce = new QGraphicsColorizeEffect;
    qgce->setColor(Qt::black);
    qgce->setEnabled(false);
    chartView->setGraphicsEffect(qgce);


    connect(chartTypeComboBox, QOverload<int>::of(&QComboBox::activated), this, &ChartWidget::changeChartType);
    connect(checkBoxBW,  &QCheckBox::stateChanged, this, &ChartWidget::switchColorTheme);
}

void ChartWidget::drawChart(shared_ptr<QList<Record>> data)
{

    QChart* oldChart = chartView->chart();
    if(!oldChart)
        delete oldChart;
    shared_ptr<IChartCreator> creator = m_factory->getCreator(m_currentType);
    m_data = data;
    QChart* chart = creator->createChart(data);
    if(chart)
    {
        chartView->setChart(chart);
    }
    chartView->chart()->setGraphicsEffect(qgce);


}

void ChartWidget::changeChartType(int type)
{
    QChart* oldChart = chartView->chart();
    if(!oldChart)
        delete oldChart;

    m_currentType = static_cast<ChartType>(type);
    shared_ptr<IChartCreator> creator = m_factory->getCreator(m_currentType);
    if(!m_data)
        return;
    QChart* chart = creator->createChart(m_data);
    if(chart)
    {
        chartView->setChart(chart);
    }
    chartView->chart()->setGraphicsEffect(qgce);
}


void ChartWidget::switchColorTheme(int state){
    qgce->setEnabled(Qt::Checked == state);
    chartView->chart()->setGraphicsEffect(qgce);
}


// void ChartWidget::switchColorTheme(int state)
// {
//     if (!m_data || !chartView || !chartView->chart())
//         return;

//     enableBlackAndWhite = (Qt::Checked == state);

//     QChart* currentChart = chartView->chart();

//     // Проверка наличия эффекта
//     QGraphicsEffect* existingEffect = currentChart->graphicsEffect();
//     QGraphicsColorizeEffect* colorEffect = nullptr;
//     qgce = colorEffect;
//     if (!existingEffect) {
//         colorEffect = new QGraphicsColorizeEffect(currentChart);
//         colorEffect->setColor(Qt::black); // Черный цвет для ч/б режима
//         colorEffect->setStrength(1.0);    // Полная интенсивность эффекта
//         currentChart->setGraphicsEffect(colorEffect);
//     } else {
//         colorEffect = qobject_cast<QGraphicsColorizeEffect*>(existingEffect);
//         if (!colorEffect) {

//             colorEffect = new QGraphicsColorizeEffect(currentChart);
//             colorEffect->setColor(Qt::black);
//             colorEffect->setStrength(1.0);
//             currentChart->setGraphicsEffect(colorEffect);
//         }
//     }

//     colorEffect->setEnabled(enableBlackAndWhite);

//     chartView->update();
// }

void ChartWidget::printPDF() {
    QString strFilter = "*.pdf";
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Сохранить файл",
        "D:/repoVlada/old/sdt_lab3/files/chartPDF.pdf",
        strFilter
        );

    if (fileName.isEmpty()) return;

    if (!fileName.endsWith(".pdf", Qt::CaseInsensitive)) {
        fileName += ".pdf";
    }


    QPdfWriter writer(fileName);
    writer.setCreator("PrintChartsPDF");
    writer.setPageSize(QPagedPaintDevice::A4);
    writer.setResolution(300);

    QPainter painter(&writer);
    if (chartView) {
        chartView->render(&painter);
    }
    painter.end();
}

