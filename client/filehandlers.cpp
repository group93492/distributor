#include "filehandlers.h"

void FilesSerializator::writeFiles()
{
    getGlobalInfo();
    QTcpSocket *socket = (QTcpSocket*)sender();
    while(!m_listOfFiles.isEmpty())
    {
        QFile file(m_listOfFiles.first());
        m_fileSize = file.size();
        m_oldSentSize = 0;
        m_newSentSize = 0;
        emit fileInfo(m_listOfFiles.first(), m_fileSize);
        file.open(QIODevice::ReadOnly);
        char *data = new char[32 * 1024];
        quint64 length;
        while(!file.atEnd())
        {
            length = file.read(data, 32 * 1024);
            m_newSentSize += length;
            socket->write(data, length);
            //socket->flush();
            QCoreApplication::processEvents();
            socket->waitForBytesWritten();
        }
        delete [] data;
        file.close();
        m_listOfFiles.removeAt(0);
        checkTransferState();
        QCoreApplication::processEvents();
    }
    emit finishGlobalTransfer();
}

void FilesSerializator::setFileNames(QStringList fileNames)
{
    m_listOfFiles = fileNames;
}

void FilesSerializator::getGlobalInfo()
{
    qint64 size = 0;
    QFile file;
    for(int i = 0; i < m_listOfFiles.size(); i++)
    {
        file.setFileName(m_listOfFiles.value(i));
        size += file.size() / 1024;
    }
    emit transferInfo(m_listOfFiles.size(), size);
}

void FilesSerializator::checkTransferState()
{
    emit state(m_newSentSize - m_oldSentSize);
    m_oldSentSize = m_newSentSize;
    if(m_oldSentSize == m_fileSize)
        emit finishFileTransfer();
}
