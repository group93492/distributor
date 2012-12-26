#include "tcpclient.h"

TcpClient::TcpClient(QObject *parent) :
    QObject(parent),
    m_nextBlockSize(0)
{
}

void TcpClient::start(QTcpSocket *socket, QString nickname)
{
    m_tcpSocket = socket;
    m_nickname = nickname;
    connect(m_tcpSocket, SIGNAL(readyRead()), SLOT(clientGotNewMessage()));
    connect(m_tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(socketError(QAbstractSocket::SocketError)));
    sendStartInfoRequest();
}

void TcpClient::stop()
{
    if(!m_tcpSocket)
        return;
    m_tcpSocket->close();
    delete m_tcpSocket;
}

void TcpClient::sendStartInfoRequest()
{
    StartInfoRequest *msg = new StartInfoRequest();
    sendMessageToServer(msg);
}

void TcpClient::requestFolderContents(QString path)
{
    qDebug() << "Request folder contents:" << path;
    FolderContentRequest *msg = new FolderContentRequest;
    msg->path = path;
    sendMessageToServer(msg);
    delete msg;
}

void TcpClient::requestActionWithFiles(QString fileName, ActionType type)
{
    ActionWithFileRequest *msg = new ActionWithFileRequest;
    msg->fileName = fileName;
    msg->actionType = int(type);
    sendMessageToServer(msg);
    delete msg;
}

void TcpClient::setBufferData(QStringList folders, QStringList files, ActionType type)
{
    m_buffer.folders = folders;
    m_buffer.files = files;
    m_buffer.type = type;
}

void TcpClient::clientGotNewMessage()
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
        MessageHeader *header = new MessageHeader(input);
        MessageType msgType = (MessageType) header->messageType;
        delete header;
        switch (msgType)
        {
        case mtStartInfoAnswer:
        {
            StartInfoAnswer *msg = new StartInfoAnswer(input);
            processMessage(msg);
            delete msg;
            break;
        }
        case mtFolderContentsAnswer:
        {
            FolderContentAnswer *msg = new FolderContentAnswer(input);
            processMessage(msg);
            delete msg;
            break;
        }
        default:
        {
            socket->readAll().clear();
            qDebug() << "Client received unknown-typed message" << msgType;
            break;
        }
        }
        m_nextBlockSize = 0;
    }
}

void TcpClient::socketError(QAbstractSocket::SocketError)
{
    QMessageBox::warning(0, "Error!", m_tcpSocket->errorString(), QMessageBox::Ok);
}

void TcpClient::sendMessageToServer(MessageBody *msgBody) const
{
    QByteArray arrBlock;
    QDataStream output(&arrBlock, QIODevice::WriteOnly);
    output.setVersion(QDataStream::Qt_4_7);
    output << quint16(0);
    MessageHeader *header = new MessageHeader(msgBody);
    header->pack(output);
    msgBody->pack(output);
    delete header;
    output.device()->seek(0);
    output << quint16(arrBlock.size() - sizeof(quint16));
    m_tcpSocket->write(arrBlock);
}

void TcpClient::processMessage(StartInfoAnswer *msg)
{
    emit contents(msg->folders, msg->files);
    emit rights(msg->rights);
}

void TcpClient::processMessage(FolderContentAnswer *msg)
{
    emit contents(msg->folders, msg->files);
}
