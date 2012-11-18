#include "tcpclient.h"

ChatClient::ChatClient(QObject *parent) :
    QObject(parent),
    m_nextBlockSize(0)
{
}

void ChatClient::start(QTcpSocket *socket)
{
    m_tcpSocket = socket;
    connect(m_tcpSocket, SIGNAL(readyRead()), SLOT(clientGotNewMessage()));
    connect(m_tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(socketError(QAbstractSocket::SocketError)));
}

void ChatClient::stop()
{
    if(!m_tcpSocket)
        return;
    m_tcpSocket->close();
    delete m_tcpSocket;
}

void ChatClient::clientGotNewMessage()
{
    QTcpSocket *socket = (QTcpSocket*)sender();
    QDataStream input(socket);
    input.setVersion(QDataStream::Qt_4_7);
    while (true)
    {
        if(!m_nextBlockSize)
        {
            if(socket->bytesAvailable() < sizeof(quint16))
                break;
            input >> m_nextBlockSize;
        }
        if(socket->bytesAvailable() < m_nextBlockSize)
            break;
        //message in in <input>, unpack it
        ChatMessageHeader *header = new ChatMessageHeader(input);
        MessageType msgType = (MessageType) header->messageType;
        delete header;
        switch (msgType)
        {
        default:
            {
                qDebug() << "Client received unknown-typed message" << msgType;
                break;
            }
        }
        m_nextBlockSize = 0;
    }
}

void ChatClient::socketError(QAbstractSocket::SocketError)
{
    QMessageBox::warning(0, "Error!", m_tcpSocket->errorString(), QMessageBox::Ok);
}

void ChatClient::sendMessageToServer(ChatMessageBody *msgBody) const
{
    QByteArray arrBlock;
    QDataStream output(&arrBlock, QIODevice::WriteOnly);
    output.setVersion(QDataStream::Qt_4_7);
    output << quint16(0);
    ChatMessageHeader *header = new ChatMessageHeader(msgBody);
    header->pack(output);
    msgBody->pack(output);
    delete header;
    output.device()->seek(0);
    output << quint16(arrBlock.size() - sizeof(quint16));
    m_tcpSocket->write(arrBlock);
}