#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QStringList>
#include <QSplitter>

#include "Widgets/filesystemwidget.h"
#include "Widgets/chartwidget.h"
#include "DataReaders/idatareader.h"
#include "DataReaders/jsondatareader.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onFileSelected(const QFileInfo& fileInfo) const;

signals:
    void onFileRead(const QList<Record>& data) const;

private:
    void makeConnection() const;

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
