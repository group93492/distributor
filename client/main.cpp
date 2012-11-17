#include <QApplication>
#include <QObject>
#include "authdialog.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    AuthDialog authDialog;
    authDialog.show();
    QObject::connect(&authDialog, SIGNAL(startClient(QTcpSocket*,QString)), &w, SLOT(startClient(QTcpSocket*,QString)));
    return a.exec();
}
