#include "mainwindow.h"

MainWindow::MainWindow( std::shared_ptr<IDataReaderFactory> dataReaderFactory,
                        std::shared_ptr<IChartCreatorsFactory> chartCreatorsFactory,
                        QWidget *parent)
    : QMainWindow(parent)
{

    QStringList filters = {"*.sqlite", "*.json"};

    fileSystemWidget = new FileSystemWidget(dataReaderFactory, this, filters);


    /*Создание Actions*/
    openCatalogAction = new QAction("Открыть...", this);
    printChartAction = new QAction("Печать в PDF", this);
    exitAction = new QAction("Закрыть", this);

    /*Создание меню*/
    menu = menuBar()->addMenu(tr("&File"));
    menu->addAction(openCatalogAction);
    menu->addAction(printChartAction);
    menu->addAction(exitAction);

    /*Создани Chart*/
    chartWidget = new ChartWidget(chartCreatorsFactory);

    QSplitter* splitter = new QSplitter(Qt::Horizontal, this);
    if(splitter != nullptr && fileSystemWidget != nullptr && chartWidget != nullptr){
    splitter->addWidget(fileSystemWidget);
    splitter->addWidget(chartWidget);
    }

    QVBoxLayout* mainLayout = new QVBoxLayout();
    if(mainLayout != nullptr ){
        mainLayout->addWidget(splitter);
    }

    QWidget* central = new QWidget(this);
    if(central != nullptr ){
    central->setLayout(mainLayout);
    }

    setCentralWidget(central);

    makeConnection();

}

MainWindow::~MainWindow() {}

void MainWindow::makeConnection() const
{
    /*Подключение Actions*/
    connect(openCatalogAction, &QAction::triggered, fileSystemWidget, &FileSystemWidget::openNewCatalog);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
    connect(printChartAction,  &QAction::triggered, chartWidget, &ChartWidget::printPDF);

    /*Подключение считывания данных и отрисовку графиков*/
    connect(fileSystemWidget, &FileSystemWidget::fileSelected, chartWidget, &ChartWidget::drawChart);
}


