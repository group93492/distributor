#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->filesLayout->addWidget(&m_fileManager);
    connect(&m_fileManager, SIGNAL(pathChanged(QString)), ui->pathLineEdit, SLOT(setText(QString)));
    connect(&m_fileManager, SIGNAL(pathChanged(QString)), &m_tcpClient, SLOT(requestFolderContents(QString)));
    connect(&m_tcpClient, SIGNAL(contents(QStringList,QStringList)), &m_fileManager, SLOT(addContents(QStringList,QStringList)));
    connect(&m_tcpClient, SIGNAL(rights(quint8)), this, SLOT(setRights(quint8)));
//    QStringList list1;
//    list1 << "Folder1" << "Folder2" << "Folder3";
//    QStringList list2;
//    list2 << "File1" << "File2" << "File3" << "File4";
//    m_fileManager.addContents(list1, list2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startClient(QTcpSocket *socket, QString nick)
{
    ui->statusBar->showMessage("Connected!");
    ui->nickLabel->setText(QString("Your nick: <b>%1</b>").arg(nick));
    ui->serverLabel->setText("Server: " + socket->peerAddress().toString() + QString::number(socket->peerPort()));
    m_tcpClient.start(socket, nick);
    show();
}

void MainWindow::setRights(quint8 rights)
{
    QString str;
    if(rights / 128)
        str += "/Download/";
    else
        ui->mainToolBar->actions()[0]->setEnabled(false);
    if(rights / 64)
        str += "/Upload/";
    else
        ui->mainToolBar->actions()[1]->setEnabled(false);
    if(rights / 32)
        str += "/Delete/";
    else
        ui->mainToolBar->actions()[3]->setEnabled(false);
    ui->rigthsLabel->setText("Your rights:" + str);

}
