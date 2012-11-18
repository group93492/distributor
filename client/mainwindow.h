#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QTcpSocket>
#include <QHostAddress>
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
    
private:
    Ui::MainWindow *ui;
    FileManager m_fileManager;
};

#endif // MAINWINDOW_H
