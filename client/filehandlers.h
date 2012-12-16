#ifndef FILEHANDLERS_H
#define FILEHANDLERS_H

#include <QObject>
#include <QStringList>
#include <QtNetwork>

class FilesSerializator : public QObject
{
    Q_OBJECT
public slots:
    void writeFiles();
    void setFileNames(QStringList fileNames);

private:
    QStringList m_listOfFiles;
    qint64 m_fileSize;
    qint64 m_newSentSize;
    qint64 m_oldSentSize;
    void getGlobalInfo();

private slots:
    void checkTransferState();

signals:
    void transferInfo(qint8 filesCount, qint64 allFilesSize);
    void fileInfo(QString fileName, qint64 fileSize);
    void state(qint64 bytesWritten);
    void finishFileTransfer();
    void finishGlobalTransfer();
};

#endif // FILEHANDLERS_H
