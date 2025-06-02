#include "mainwindow.h"

MainWindow::MainWindow(IOCContainer &container, QWidget *parent)
    : QMainWindow(parent)
{
    registeringDependencies(container);

    QStringList filters = {"*.sqlite", "*.json"};

    fileSystemWidget = new FileSystemWidget(container.getObject<DataReaderFactory>(), this, filters);
    //setCentralWidget(fileSystemWidget);

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
    chartWidget = new ChartWidget(container.getObject<ChartCreatorsFactory>());

    QSplitter* splitter = new QSplitter(Qt::Horizontal, this);
    splitter->addWidget(fileSystemWidget);
    splitter->addWidget(chartWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(splitter);

    QWidget* central = new QWidget(this);
    central->setLayout(mainLayout);

    setCentralWidget(central);

    makeConnection();

}

MainWindow::~MainWindow() {}

void MainWindow::makeConnection() const
{
    /*Подключение Actions*/
    connect(openCatalogAction, &QAction::triggered, fileSystemWidget, &FileSystemWidget::openNewCatalog);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    /*Подключение считывания данных и отрисовку графиков*/
    connect(fileSystemWidget, &FileSystemWidget::fileSelected, chartWidget, &ChartWidget::drawChart);
}

void MainWindow::registeringDependencies(IOCContainer& container)
{
    container.registerInstance<ChartCreatorsFactory, ChartCreatorsFactory>();
    container.registerInstance<DataReaderFactory, DataReaderFactory>();
}
