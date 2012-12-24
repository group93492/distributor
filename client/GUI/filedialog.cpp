#include "filedialog.h"
#include "ui_filedialog.h"
#include <QDebug>

FileDialog::FileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileDialog)
{
    ui->setupUi(this);
    setWindowModality(Qt::ApplicationModal);
    m_treeModel.setFilter(QDir::NoDotAndDotDot | QDir::Dirs);
    m_listModel.setFilter(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs);
    m_treeModel.setRootPath(QDir::currentPath());
    m_listModel.setRootPath(QDir::homePath());
    ui->treeView->setModel(&m_treeModel);
    ui->listView->setModel(&m_listModel);
    ui->listView->setRootIndex(m_listModel.index(QDir::homePath()));
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
}

void FileDialog::on_listView_doubleClicked(const QModelIndex &index)
{
    if(m_listModel.fileInfo(index).isDir())
    {
        ui->listView->setRootIndex(m_listModel.setRootPath(m_listModel.fileInfo(index).absoluteFilePath()));
    }
}
