#include "filesystemwidget.h"

FileSystemWidget::FileSystemWidget(shared_ptr<IDataReaderFactory> factory, QWidget *parent, const QStringList &filters) : QWidget(parent)
{
    if (!factory) {
        throw std::invalid_argument("FileSystemWidget Error: DataReaderFactory dependency cannot be null.");
    }
    m_factory = factory;

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
    {
        QMessageBox::warning(nullptr, "Warning", "Catalog not selected!");
        return;
    }

    QDir dir(directory);
    QStringList files = dir.entryList(fileSystemModel->nameFilters(),QDir::Files);

    if(files.isEmpty())
    {
        QMessageBox::information(this, tr("Info"), tr("The selected directory is empty."));
        return;
    }

    fileSystemModel->setRootPath(dir.absolutePath());
    tableView->setRootIndex(fileSystemModel->index(dir.absolutePath()));

}

void FileSystemWidget::modelItemSelected(const QModelIndex &current) const
{
    QFileInfo fileInfo = fileSystemModel->fileInfo(current);
    QString suffix = fileInfo.suffix();

    try
    {
        shared_ptr<QList<Record>> data = m_factory->getReader(suffix)->readData(fileInfo);
        emit fileSelected(data);
    }
    catch(const QString e)
    {
        QMessageBox::critical(nullptr, "Warning", e);
    }

}
