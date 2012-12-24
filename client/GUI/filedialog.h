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
    ~FileDialog();
    
private slots:
    void on_treeView_clicked(const QModelIndex &index);

    void on_listView_doubleClicked(const QModelIndex &index);

private:
    Ui::FileDialog *ui;
    QFileSystemModel m_treeModel;
    QFileSystemModel m_listModel;
};

#endif // FILEDIALOG_H
