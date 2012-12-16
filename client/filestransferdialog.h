#ifndef FILESTRANSFER_H
#define FILESTRANSFER_H

#include <QWidget>

namespace Ui {
class FilesTransfer;
}

class FilesTransfer : public QWidget
{
    Q_OBJECT
    
public:
    explicit FilesTransfer(QWidget *parent = 0);
    ~FilesTransfer();
    void setFileSize(qint64 Kb);
    void setFileName(QStringList fileName);

public slots:
    void setGlobalTransferInfo(qint8 filesCount, qint64 allFilesSize);
    void setFileInfo(QString fileName, qint64 size);
    void setTransferState(qint64 bytesWritten);
    void finishTransfer();
    void finishGlobalTransfer();
    
private:
    Ui::FilesTransfer *ui;
    qint8 m_currentFileCount;
    qint8 m_filesCount;
};

#endif // FILESTRANSFER_H
