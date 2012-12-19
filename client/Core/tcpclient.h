#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QMessageBox>
#include "protocol.h"

struct buffer
{
    QStringList folders;
    QStringList files;
    ActionType type;
};

class TcpClient : public QObject
{
    Q_OBJECT

public:
    explicit TcpClient(QObject *parent = 0);
    void start(QTcpSocket *socket, QString nickname);
    void stop();
    void sendStartInfoRequest();
    void requestActionWithFiles(QString fileName, ActionType type);
    void setBufferData(QStringList folders, QStringList files, ActionType type);

public slots:
    void requestFolderContents(QString path);

private:
    QTcpSocket *m_tcpSocket;
    quint16 m_nextBlockSize;
    QString m_nickname;
    buffer m_buffer;
    void sendMessageToServer(MessageBody *msgBody) const;
    void processMessage(StartInfoAnswer *msg);
    void processMessage(FolderContentAnswer *msg);

private slots:
    void clientGotNewMessage();
    void socketError(QAbstractSocket::SocketError);

signals:
    void contents(QStringList folders, QStringList files);
    void rights(quint8 rights);
};

#endif // TCPCLIENT_H
