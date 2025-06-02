#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QStringList>
#include <QSplitter>

#include "IOC/iocconteiner.h"
#include "Widgets/filesystemwidget.h"
#include "Widgets/chartwidget.h"
#include "DataReaders/idatareader.h"
#include "DataReaders/jsondatareader.h"
#include "ChartCreatorsFactory/chartcreatorsfactory.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(IOCContainer& container, QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void onFileRead(shared_ptr<QList<Record>> data) const;

private:
    void makeConnection() const;
    void registeringDependencies(IOCContainer& container);

private:
    FileSystemWidget* fileSystemWidget;
    ChartWidget* chartWidget;

    IDataReader* dataReader;

    QMenu* menu;
    QAction* openCatalogAction;
    QAction* printChartAction;
    QAction* exitAction;

};
#endif // MAINWINDOW_H
