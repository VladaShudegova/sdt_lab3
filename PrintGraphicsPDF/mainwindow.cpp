
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
#include <QDirIterator>
#include <QFileDialog>
#include <QMessageBox>


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

        createMenu();

        QString homePath = QDir::homePath();

        partModel = new QFileSystemModel(this);
        partModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
        partModel->setRootPath(homePath);

        tableView = new QTableView;
        tableView->setModel(partModel);

        QSplitter *splitter = new QSplitter(this);
        splitter->addWidget(tableView);
        splitter->addWidget(themeWidget);


        setCentralWidget(splitter);

        QItemSelectionModel *selectionModel = tableView->selectionModel();

        //Выполняем соединения слота и сигнала который вызывается когда осуществляется выбор элемента в TreeView
        connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &MainWindow::on_selectionChangedSlot);

        //Пример организации установки курсора в TreeView относительно модельного индекса
        QItemSelection toggleSelection;
        //Объявили модельный индекс topLeft
        QModelIndex topLeft;
        //Получили индекс из модели
        topLeft = partModel->index(homePath);
        toggleSelection.select(topLeft, topLeft);
        selectionModel->select(toggleSelection, QItemSelectionModel::Toggle);



    }

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createMenu(){
    QMenu *fileMenu = menuBar()->addMenu("Файл");

    m_loadAction = new QAction("Загрузить данные", this);
    fileMenu->addAction(m_loadAction);

    m_printAction = new QAction("Печать", this);
    fileMenu->addAction(m_printAction);

    m_exitAction = new QAction("Выход", this);
    fileMenu->addAction(m_exitAction);

    connect(m_loadAction, &QAction::triggered, this, &MainWindow::loadFolder);
    connect(m_printAction, &QAction::triggered, this, &MainWindow::printPDF);
    connect(m_exitAction, &QAction::triggered, this, &QWidget::close);
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
        // Здесь будет код для чтения данных из файла и обновления графика


        file.close();
    }
}
// MainWindow.cpp


void MainWindow::loadFolder()
{
    // 1. Диалог выбора папки
    const QString dirPath = QFileDialog::getExistingDirectory(
        this,
        tr("Открыть папку с файлами"),
        QString(),                                            // стартовая директория
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (dirPath.isEmpty())
        return;                                     // пользователь нажал Отмена

    // 2. Итератор по *.txt внутри папки (и под-папок при желании)
    QDirIterator it(dirPath,
                    QStringList() << "",        // фильтр расширений
                    QDir::Files,
                    QDirIterator::Subdirectories);   // или  QDirIterator::NoIteratorFlags чтобы без под-папок

    // Соберём статистику, вдруг пригодится
    int opened  = 0;
    int failed  = 0;

    // 3. Читаем каждый файл по очереди
    while (it.hasNext())
    {
        const QString filePath = it.next();

        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            ++failed;
            QMessageBox::warning(this, tr("Ошибка"),
                                 tr("Не удалось открыть файл %1:\n%2.")
                                     .arg(QDir::toNativeSeparators(filePath),
                                          file.errorString()));
            continue;
        }

        ++opened;
        QTextStream in(&file);

        /* ----------------------------------------------------------------
         *  Здесь ваш парсинг / обновление графика
         *  Например:
         *      QVector<double> dataX, dataY;
         *      parseFile(in, dataX, dataY);
         *      plot->addCurve(dataX, dataY);
         * ----------------------------------------------------------------*/
    }

    // 4. Итоговое сообщение (по желанию)
    QMessageBox::information(this, tr("Загрузка завершена"),
                             tr("Открыто файлов: %1\nНе удалось открыть: %2")
                                 .arg(opened)
                                 .arg(failed));
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

void MainWindow::on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected)
{
    //Q_UNUSED(selected);
    Q_UNUSED(deselected);

    QModelIndex index = tableView->selectionModel()->currentIndex();

    QModelIndexList indexs =  selected.indexes();

    QString filePath = "";

    // Размещаем информацию в statusbar относительно выделенного модельного индекса
    /*
     * Смотрим, сколько индексов было выделено.
     * В нашем случае выделяем только один, следовательно всегда берем только первый.
    */
    if (indexs.count() >= 1) {
        QModelIndex ix =  indexs.constFirst();
        filePath = partModel->filePath(ix);
        this->statusBar()->showMessage("Выбранный путь : " + partModel->filePath(indexs.constFirst()));
    }

    /*
     * Получив выбранные данные из левой части filePath(путь к папке/файлу).
     * Для представления в правой части устанваливаем корневой индекс относительно filePath.
     * Табличное представление отображает только файлы, находящиеся в filePath(папки не отображает)
     */
    // tableView->setRootIndex(partModel->setRootPath(filePath));
}









