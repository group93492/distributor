#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <QDialog>
#include <QFileSystemModel>

namespace Ui {
class FileDialog;
}

class FileDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit FileDialog(QWidget *parent = 0);
    QStringList selectedFolders();
    QStringList selectedFiles(QStringList folders);
    QModelIndexList selectedItems();
    ~FileDialog();
    
private slots:
    void on_treeView_clicked(const QModelIndex &index);
    void on_listView_doubleClicked(const QModelIndex &index);

    void on_pathEdit_textChanged(const QString &arg1);

private:
    Ui::FileDialog *ui;
    QFileSystemModel m_treeModel;
    QFileSystemModel m_listModel;
    QModelIndexList m_selectedItems;
    QStringList getFolderListRecursive(QString path);

protected:
    void accept();
};

#endif // FILEDIALOG_H
