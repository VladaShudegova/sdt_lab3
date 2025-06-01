#ifndef FILESYSTEMWIDGET_H
#define FILESYSTEMWIDGET_H

#include <QWidget>
#include <QFileSystemModel>
#include <QTableView>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QStringList>

class FileSystemWidget : public QWidget
{
    Q_OBJECT
public:
    FileSystemWidget(QWidget *parent = nullptr, const QStringList& filters = {});

public slots:
    void openNewCatalog();
    void modelItemSelected(const QModelIndex& current) const;

signals:
    void fileSelected(const QFileInfo& fileInfo) const;

private:
    QFileSystemModel* fileSystemModel;
    QTableView* tableView;
};

#endif // FILESYSTEMWIDGET_H
