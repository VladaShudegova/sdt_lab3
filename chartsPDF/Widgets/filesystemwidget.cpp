#include "filesystemwidget.h"

FileSystemWidget::FileSystemWidget(QWidget *parent, const QStringList& filters) : QWidget(parent)
{

    QVBoxLayout* rootLayout = new QVBoxLayout(this);

    fileSystemModel = new QFileSystemModel(this);
    fileSystemModel->setRootPath(QDir::rootPath());
    fileSystemModel->setFilter(QDir::Files | QDir::NoDotAndDotDot);
    fileSystemModel->setNameFilters(filters);
    fileSystemModel->setNameFilterDisables(false);

    tableView = new QTableView(this);
    tableView->setModel(fileSystemModel);
    tableView->setRootIndex(fileSystemModel->index(QDir::currentPath()));

    rootLayout->addWidget(tableView);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(tableView, &QTableView::activated, this, &FileSystemWidget::modelItemSelected);
}

void FileSystemWidget::openNewCatalog()
{
    QString directory = QFileDialog::getExistingDirectory(this,
                                                    tr("Открыть"),
                                                    fileSystemModel->rootPath(),
                                                    QFileDialog::ShowDirsOnly);

    if(directory.isEmpty())
        return;

    QDir dir(directory);

    if(dir.isEmpty())
    {
        //Вызвать предупреждение о пустой папке
    }

    fileSystemModel->setRootPath(dir.absolutePath());
    tableView->setRootIndex(fileSystemModel->index(dir.absolutePath()));

}

void FileSystemWidget::modelItemSelected(const QModelIndex &current) const
{
    emit fileSelected(fileSystemModel->fileInfo(current));
}
