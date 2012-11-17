#ifndef AUTHDIALOG_H
#define AUTHDIALOG_H

#include <QWidget>
#include <QtNetwork/QTcpSocket>
#include <QMessageBox>
#include <QCryptographicHash>
#include "protocol.h"

namespace Ui {
class AuthDialog;
}

class AuthDialog : public QWidget
{
    Q_OBJECT
    
public:
    enum AuthDialogAction {
        AuthorizationAction,
        RegistrationAction
    };
    explicit AuthDialog(QWidget *parent = 0);
    ~AuthDialog();
    
private:
    Ui::AuthDialog *ui;
    QTcpSocket *m_socket;
    quint16 m_nextBlockSize;
    AuthDialogAction m_action;
    void sendMessageToServer(ChatMessageBody *body);
    void processMessage(RegistrationAnswer *msg);
    void processMessage(AuthorizationAnswer *msg);
    void createSocket();
    void destructSocket();
    bool checkInputFields();

private slots:
    void connected();
    void gotMessage();
    void socketError(QAbstractSocket::SocketError error);

    void on_loginButton_clicked();

    void on_regButton_clicked();

signals:
    void startClient(QTcpSocket *socket, QString nick);
};

#endif // AUTHDIALOG_H
