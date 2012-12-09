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

public:
    explicit TcpClient(QObject *parent = 0);
    void start(QTcpSocket *socket, QString nickname);
    void stop();
    void sendStartInfoRequest();

public slots:
    void requestFolderContents(QString path);

private:
    QTcpSocket *m_tcpSocket;
    quint16 m_nextBlockSize;
    void sendMessageToServer(ChatMessageBody *msgBody) const;
    void processMessage(StartInfoAnswer *msg);
    void processMessage(FolderContentsAnswer *msg);
    QString m_nickname;

private slots:
    void clientGotNewMessage();
    void socketError(QAbstractSocket::SocketError);

signals:
    void contents(QStringList folders, QStringList files);
    void rigths(QString rights);
};

#endif // TCPCLIENT_H
