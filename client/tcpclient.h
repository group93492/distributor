#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QMessageBox>
#include "protocol.h"

class TcpClient : public QObject
{
    Q_OBJECT
private:
    QTcpSocket *m_tcpSocket;
    quint16 m_nextBlockSize;
    void sendMessageToServer(ChatMessageBody *msgBody) const;

public:
    explicit TcpClient(QObject *parent = 0);
    void start(QTcpSocket *socket);
    void stop();

private slots:
    void clientGotNewMessage();
    void socketError(QAbstractSocket::SocketError);
};

#endif // TCPCLIENT_H
