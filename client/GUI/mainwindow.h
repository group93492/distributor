#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QTcpSocket>
#include <QHostAddress>
#include "Core/tcpclient.h"
#include "filemanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void startClient(QTcpSocket *socket, QString nick);
    void onDownloadButtonClicked();
    
private:
    Ui::MainWindow *ui;
    FileManager m_fileManager;
    TcpClient m_tcpClient;

private slots:
    void setRights(quint8 rights);
};

#endif // MAINWINDOW_H
