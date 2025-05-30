
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QTime>
#include <QLabel>
#include <QSplitter>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>


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
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtCore/QTime>
#include <QtCharts/QBarCategoryAxis>
#include <QPainter>
#include <QPdfWriter>
#include <QFileDialog>
#include <QPrinter>
#include <QPrintDialog>

QT_CHARTS_BEGIN_NAMESPACE
    class QChartView;
    class QChart;
QT_CHARTS_END_NAMESPACE

    MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
    {
        ui->setupUi(this);

        this->setWindowTitle("PrintChartsPDF");

        themeWidget = new ThemeWidget();

        // Устанавливаем размер главного окна
        this->setGeometry(100, 100, 1500, 500);
        this->setStatusBar(new QStatusBar(this));
        this->statusBar()->showMessage("Выберите файл БД");

        // Используем встроенный menuBar
        QMenu *fileMenu = menuBar()->addMenu("Файл");

        m_loadAction = new QAction("Загрузить данные", this);
        fileMenu->addAction(m_loadAction);

        m_printAction = new QAction("Печать", this);
        fileMenu->addAction(m_printAction);

        m_exitAction = new QAction("Выход", this);
        fileMenu->addAction(m_exitAction);

        // Создаем временную метку
        QLabel *justTmpLabel = new QLabel(this);
        justTmpLabel->setText("------В этой части будем отображать файлы с данными для графика----");

        // Создаем сплиттер и добавляем виджеты
        QSplitter *splitter = new QSplitter(this);
        splitter->addWidget(justTmpLabel);
        splitter->addWidget(themeWidget);

        // Устанавливаем сплиттер как центральный виджет
        setCentralWidget(splitter);

        // Подключаем сигналы
        connect(m_loadAction, &QAction::triggered, this, &MainWindow::loadFile);
        connect(m_printAction, &QAction::triggered, this, &MainWindow::printPDF);
        connect(m_exitAction, &QAction::triggered, this, &QWidget::close);
    }

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::loadFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Открыть файл"), "",
                                                    tr("Текстовые файлы (*.txt);;Все файлы (*)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::warning(this, tr("Ошибка"),
                                 tr("Не удалось открыть файл %1:\n%2.")
                                     .arg(QDir::toNativeSeparators(fileName),
                                          file.errorString()));
            return;
        }

        QTextStream in(&file);
        // Здесь добавьте код для чтения данных из файла и обновления графика
        // Например:
        // m_dataTable = readDataFromFile(in);
        // updateChart();

        file.close();
    }
}


void MainWindow::printPDF() {
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
    if (themeWidget && themeWidget->getChartView()) {
        themeWidget->getChartView()->render(&painter);
    }
    painter.end();
}









