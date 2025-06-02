#ifndef FILESYSTEMWIDGET_H
#define FILESYSTEMWIDGET_H

#include <QWidget>
#include <QFileSystemModel>
#include <QTableView>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QStringList>
#include <QMessageBox>

#include "DataReaders/idatareader.h"
#include "DataReaders/datareaderfactory.h"

class FileSystemWidget : public QWidget
{
    Q_OBJECT
public:
    FileSystemWidget(shared_ptr<DataReaderFactory> factory, QWidget *parent = nullptr, const QStringList& filters = {});

public slots:
    void openNewCatalog();
    void modelItemSelected(const QModelIndex& current) const;

signals:
    void fileSelected(shared_ptr<QList<Record>> data) const;

private:
    QFileSystemModel* fileSystemModel;
    QTableView* tableView;
    shared_ptr<DataReaderFactory> m_factory;
};

#endif // FILESYSTEMWIDGET_H
