#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->filesLayout->addWidget(&m_fileManager);
    connect(&m_fileManager, SIGNAL(pathChanged(QString)), ui->pathLineEdit, SLOT(setText(QString)));
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
    m_tcpClient.start(socket);
    show();
}
