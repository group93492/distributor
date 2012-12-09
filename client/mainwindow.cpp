#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->filesLayout->addWidget(&m_fileManager);
    connect(&m_fileManager, SIGNAL(pathChanged(QString)), ui->pathLineEdit, SLOT(setText(QString)));
    connect(&m_tcpClient, SIGNAL(contents(QStringList,QStringList)), &m_fileManager, SLOT(addContents(QStringList,QStringList)));
    connect(&m_tcpClient, SIGNAL(rigths(QString)), this, SLOT(setRigths(QString)));
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

void MainWindow::setRigths(QString rigths)
{
    ui->rigthsLabel->setText("Your rigths:" + rigths);
}
