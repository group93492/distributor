#include "filedialog.h"
#include "ui_filedialog.h"

FileDialog::FileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileDialog)
{
    ui->setupUi(this);
    m_treeModel.setFilter(QDir::NoDotAndDotDot | QDir::Dirs);
    m_listModel.setFilter(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs);
    m_treeModel.setRootPath(QDir::currentPath());
    m_listModel.setRootPath(QDir::homePath());
    ui->treeView->setModel(&m_treeModel);
    ui->listView->setModel(&m_listModel);
    ui->listView->setRootIndex(m_listModel.index(QDir::homePath()));
    ui->pathEdit->setText(QDir::homePath());
    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(3);
}

FileDialog::~FileDialog()
{
    delete ui;
}

void FileDialog::on_treeView_clicked(const QModelIndex &index)
{
    QString path = m_treeModel.fileInfo(ui->treeView->selectionModel()->currentIndex()).absoluteFilePath();
    ui->listView->setRootIndex(m_listModel.setRootPath(path));
    ui->pathEdit->setText(path);
}

void FileDialog::on_listView_doubleClicked(const QModelIndex &index)
{
    if(m_listModel.fileInfo(index).isDir())
        ui->listView->setRootIndex(m_listModel.setRootPath(m_listModel.fileInfo(index).absoluteFilePath()));
    ui->listView->selectionModel()->clearSelection();
    if(m_listModel.fileInfo(index).isDir())
        ui->pathEdit->setText(m_listModel.fileInfo(index).absoluteFilePath());
}

QStringList FileDialog::getFolderListRecursive(QString path)
{
    QDir dir(path);
    QStringList returnList;
    QFileInfoList list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    for(int i = 0; i < list.size(); i++)
        if(list.value(i).isDir())
        {
            returnList.append(list.value(i).absoluteFilePath());
            returnList.append(getFolderListRecursive(list.value(i).absoluteFilePath()));
        }
    return returnList;
}

void FileDialog::accept()
{
    m_selectedItems = ui->listView->selectionModel()->selectedIndexes();
    QDialog::accept();
}

QStringList FileDialog::selectedFolders()
{
    QStringList stringList;
    for(int i = 0; i < m_selectedItems.size(); i++)
        if(m_listModel.fileInfo(m_selectedItems.value(i)).isDir())
        {
            stringList.append(m_listModel.fileInfo(m_selectedItems.value(i)).absoluteFilePath());
            stringList.append(getFolderListRecursive(m_listModel.fileInfo(m_selectedItems.value(i)).absoluteFilePath()));
        }
    return stringList;
}

QStringList FileDialog::selectedFiles(QStringList folders)
{
    QStringList files;
    QFileInfoList fileInfoList;
    QDir dir;
    for(int i = 0; i < folders.size(); i++)
    {
        dir.setPath(folders.value(i));
        fileInfoList = dir.entryInfoList(QDir::Files);
        for(int i = 0; i < fileInfoList.size(); i++)
            files.append(fileInfoList.value(i).absoluteFilePath());
    }
    for(int i = 0; i < m_selectedItems.size(); i++)
        if(m_listModel.fileInfo(m_selectedItems.value(i)).isFile())
            files.append(m_listModel.fileInfo(m_selectedItems.value(i)).absoluteFilePath());
    return files;
}

QModelIndexList FileDialog::selectedItems()
{
    return m_selectedItems;
}

void FileDialog::on_pathEdit_textChanged(const QString &arg1)
{
    if(QDir::isAbsolutePath(arg1))
        ui->listView->setRootIndex(m_listModel.index(arg1));
}
