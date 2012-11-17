#include "authdialog.h"
#include "ui_authdialog.h"

AuthDialog::AuthDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AuthDialog)
{
    ui->setupUi(this);
    m_socket = NULL;
    m_nextBlockSize = 0;
}

AuthDialog::~AuthDialog()
{
    delete ui;
}

void AuthDialog::sendMessageToServer(ChatMessageBody *body)
{
    QByteArray arrBlock;
    QDataStream output(&arrBlock, QIODevice::WriteOnly);
    output.setVersion(QDataStream::Qt_4_7);
    output << quint16(0);
    ChatMessageHeader *header = new ChatMessageHeader(body);
    header->pack(output);
    body->pack(output);
    delete header;
    output.device()->seek(0);
    output << quint16(arrBlock.size() - sizeof(quint16));
    m_socket->write(arrBlock);
}

void AuthDialog::processMessage(RegistrationAnswer *msg)
{
    if(msg->registrationResult)
        QMessageBox::information(this, "Registration", "You successfully registered", QMessageBox::Ok);
    else
        QMessageBox::information(this, "Registration", msg->denialReason, QMessageBox::Ok);
    destructSocket();
    ui->loginEdit->clear();
    ui->passEdit->clear();
}

void AuthDialog::processMessage(AuthorizationAnswer *msg)
{
    if(msg->authorizationResult)
    {
        emit startClient(m_socket, ui->loginEdit->text());
        hide();
    }
    else
        QMessageBox::information(this, "Authorization", msg->denialReason, QMessageBox::Ok);
}

void AuthDialog::createSocket()
{
    m_socket = new QTcpSocket;
    connect(m_socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(gotMessage()));
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));
    m_socket->connectToHost("localhost", 33034);
}

void AuthDialog::destructSocket()
{
    m_socket->close();
    delete m_socket;
    m_socket = NULL;
}

void AuthDialog::connected()
{
    if(m_action == AuthDialog::AuthorizationAction)
    {
        AuthorizationRequest *msg = new AuthorizationRequest;
        msg->username = ui->loginEdit->text();
        QByteArray array;
        array.append(ui->passEdit->text());
        msg->password = QCryptographicHash::hash(array, QCryptographicHash::Md5);
        sendMessageToServer(msg);
        delete msg;
    }
    else
    {
        RegistrationRequest *msg = new RegistrationRequest;
        msg->username = ui->loginEdit->text();
        QByteArray array;
        array.append(ui->passEdit->text());
        msg->password = QCryptographicHash::hash(array, QCryptographicHash::Md5);
        sendMessageToServer(msg);
        delete msg;
    }
}

void AuthDialog::gotMessage()
{
    QTcpSocket *socket = (QTcpSocket*)sender();
    if (socket == NULL)
        return;
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
        case mtRegistrationAnswer:
        {
            RegistrationAnswer *msg = new RegistrationAnswer(input);
            processMessage(msg);
            delete msg;
            break;
        }
        case mtAuthorizationAnswer:
        {
            AuthorizationAnswer *msg = new AuthorizationAnswer(input);
            processMessage(msg);
            delete msg;
            break;
        }
        default:
        {
            QMessageBox::warning(this, "Error", "Client received unknown-typed message", QMessageBox::Ok);
            break;
        }
        }
        m_nextBlockSize = 0;
    }
}

void AuthDialog::socketError(QAbstractSocket::SocketError error)
{
    QMessageBox::warning(this, "Error", m_socket->errorString(), QMessageBox::Ok);
    destructSocket();
}

void AuthDialog::on_loginButton_clicked()
{
    m_action = AuthDialog::AuthorizationAction;
    createSocket();
}

void AuthDialog::on_regButton_clicked()
{
    m_action = AuthDialog::RegistrationAction;
    createSocket();
}
