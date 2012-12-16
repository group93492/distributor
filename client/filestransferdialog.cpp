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
    qint32 speed = bytesWritten / 1024;
    ui->localProgressBar->setValue(ui->localProgressBar->value() + speed);
    ui->totalProgressBar->setValue(ui->totalProgressBar->value() + speed);
    qint32 seconds;
    if(speed)
        seconds = (ui->totalProgressBar->maximum() - ui->totalProgressBar->value()) / speed % 60;
    else
        seconds = 0;
    qint32 minutes = seconds / 60;
    ui->speedLabel->setText("Speed: " + QString::number(speed) + " Kb");
    ui->timeRemainingLabel->setText(QString("Times remaining: %1m:%2s").arg(minutes).arg(seconds));
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


void FilesTransfer::setGlobalTransferInfo(qint8 filesCount, qint64 allFilesSize)
{
    m_filesCount = filesCount;
    m_currentFileCount = 0;
    ui->totalInfoLabel->setText(QString("Total info: 0/%1 files").arg(filesCount));
    ui->totalProgressBar->setMaximum(allFilesSize);
}

void FilesTransfer::setFileInfo(QString fileName, qint64 size)
{
    ui->fileNameLabel->setText(QString("File's name: %1").arg(fileName.right(fileName.size() - fileName.lastIndexOf("/") - 1)));
    ui->localProgressBar->setMaximum(size / 1024);
}
