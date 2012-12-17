#include "filestransferdialog.h"
#include "ui_filestransferdialog.h"

FilesTransfer::FilesTransfer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FilesTransfer)
{
    ui->setupUi(this);
}

FilesTransfer::~FilesTransfer()
{
    delete ui;
}

void FilesTransfer::setTransferState(qint64 bytesWritten)
{
    quint32 KbytesWritten = bytesWritten / 1024;
    ui->localProgressBar->setValue(ui->localProgressBar->value() + KbytesWritten);
    ui->totalProgressBar->setValue(ui->totalProgressBar->value() + KbytesWritten);
    if(m_updateCounter == 10)
    {
        m_speed = (m_speed + KbytesWritten * 10) / 2;
        ui->speedLabel->setText("Speed: " + QString::number(m_speed) + " Kb/s");
        evalTime();
        m_updateCounter = 0;
    }
    else
        m_updateCounter++;
}

void FilesTransfer::finishTransfer()
{
    ui->localProgressBar->setValue(0);
    m_currentFileCount++;
    ui->totalInfoLabel->setText(QString("Total info: %1/%2").arg(m_currentFileCount).arg(m_filesCount));
}

void FilesTransfer::finishGlobalTransfer()
{
    hide();
}

void FilesTransfer::evalTime()
{
    quint32 seconds;
    seconds = m_speed ? (ui->totalProgressBar->maximum() - ui->totalProgressBar->value()) / m_speed : 0;
    quint32 minutes = seconds / 60;
    seconds = seconds % 60;
    ui->timeRemainingLabel->setText(QString("Times remaining: %1m:%2s").arg(minutes).arg(seconds));
}

void FilesTransfer::setGlobalTransferInfo(qint8 filesCount, qint64 allFilesSize)
{
    m_filesCount = filesCount;
    m_currentFileCount = 0;
    m_speed = 0;
    ui->totalInfoLabel->setText(QString("Total info: 0/%1 files").arg(filesCount));
    ui->totalProgressBar->setMaximum(allFilesSize);
}

void FilesTransfer::setFileInfo(QString fileName, qint64 size)
{
    ui->fileNameLabel->setText(QString("File's name: %1").arg(fileName.right(fileName.size() - fileName.lastIndexOf("/") - 1)));
    ui->localProgressBar->setMaximum(size / 1024);
}
