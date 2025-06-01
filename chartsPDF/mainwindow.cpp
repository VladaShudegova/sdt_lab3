#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    QStringList filters = {/*"*.sqlite", */"*.json"};

    fileSystemWidget = new FileSystemWidget(this, filters);
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
    chartWidget = new ChartWidget();

    QSplitter* splitter = new QSplitter(Qt::Horizontal, this);
    splitter->addWidget(fileSystemWidget);
    splitter->addWidget(chartWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(splitter);

    QWidget* central = new QWidget(this);
    central->setLayout(mainLayout);

    setCentralWidget(central);

    /*Создание IDataReader*/
    dataReader = new JSONDataReader();

    makeConnection();

}

MainWindow::~MainWindow() {}

void MainWindow::onFileSelected(const QFileInfo &fileInfo) const
{
    QList<Record> data = dataReader->readData(fileInfo);
    emit onFileRead(data);
}

void MainWindow::makeConnection() const
{
    /*Подключение Actions*/
    connect(openCatalogAction, &QAction::triggered, fileSystemWidget, &FileSystemWidget::openNewCatalog);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    /*Подключение считывания данных и отрисовку графиков*/
    connect(fileSystemWidget, &FileSystemWidget::fileSelected, this, &MainWindow::onFileSelected);
    connect(this, &MainWindow::onFileRead, chartWidget, &ChartWidget::drawChart);
}
