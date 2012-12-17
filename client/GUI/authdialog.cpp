#include "authdialog.h"
#include "ui_authdialog.h"

AuthDialog::AuthDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AuthDialog)
{
    ui->setupUi(this);
    m_socket = NULL;
    m_nextBlockSize = 0;
    m_session = new QSettings("session", QSettings::IniFormat);
    m_socket = new QTcpSocket;
    m_timer.setSingleShot(true);
    ui->loginEdit->setText(m_session->value("nickname").toString());
    move(QApplication::desktop()->geometry().width() / 2 - this->geometry().width() / 2,
             QApplication::desktop()->geometry().height() / 2 - this->geometry().height() / 2);
    //connect part
    connect(m_socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(gotMessage()));
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));
    connect(ui->configButton, SIGNAL(clicked()), &m_configDialog, SLOT(show()));
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(connectionTimeout()));
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
    unblockInterface();
    if(msg->registrationResult)
        QMessageBox::information(this, "Registration", "You successfully registered", QMessageBox::Ok);
    else
        QMessageBox::information(this, "Registration", msg->denialReason, QMessageBox::Ok);
    m_socket->close();
    ui->loginEdit->clear();
    ui->passEdit->clear();
}

void AuthDialog::processMessage(AuthorizationAnswer *msg)
{
    unblockInterface();
    if(msg->authorizationResult)
    {
        m_socket->disconnect(this);
        emit startClient(m_socket, ui->loginEdit->text());
        m_session->setValue("nickname", ui->loginEdit->text());
        hide();
    }
    else
    {
        QMessageBox::information(this, "Authorization", msg->denialReason, QMessageBox::Ok);
        m_socket->close();
    }
}

bool AuthDialog::checkInputFields()
{
    if(ui->loginEdit->text().isEmpty() || ui->passEdit->text().isEmpty())
    {
        QMessageBox::information(this, "Notification", "Empty login or password", QMessageBox::Ok);
        return false;
    }
    else
        return true;
}

void AuthDialog::blockInterface()
{
    ui->loginButton->setEnabled(false);
    ui->regButton->setEnabled(false);
}

void AuthDialog::unblockInterface()
{
    ui->loginButton->setEnabled(true);
    ui->regButton->setEnabled(true);
}

void AuthDialog::connected()
{
    if(m_action == AuthDialog::AuthorizationAction)
    {
        AuthorizationRequest *msg = new AuthorizationRequest;
        msg->username = ui->loginEdit->text();
        QByteArray array;
        array.append(ui->passEdit->text());
        msg->password = QCryptographicHash::hash(array, QCryptographicHash::Md5).toHex();
        sendMessageToServer(msg);
        delete msg;
    }
    else
    {
        RegistrationRequest *msg = new RegistrationRequest;
        msg->username = ui->loginEdit->text();
        QByteArray array;
        array.append(ui->passEdit->text());
        msg->password = QCryptographicHash::hash(array, QCryptographicHash::Md5).toHex();
        sendMessageToServer(msg);
        delete msg;
    }
    m_timer.start(10000);
}

void AuthDialog::gotMessage()
{
    m_timer.stop();
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
    unblockInterface();
    QMessageBox::warning(this, "Error", m_socket->errorString() + ". Code Error: " + QString::number(error), QMessageBox::Ok);
    m_timer.stop();
    m_socket->close();
}

void AuthDialog::on_loginButton_clicked()
{
    if(!checkInputFields())
        return;
    blockInterface();
    m_action = AuthDialog::AuthorizationAction;
    m_socket->connectToHost(m_session->value("address", "localhost").toString(), m_session->value("port", 33034).toInt());
}

void AuthDialog::on_regButton_clicked()
{
    if(!checkInputFields())
        return;
    blockInterface();
    m_action = AuthDialog::RegistrationAction;
    m_socket->connectToHost(m_session->value("address", "localhost").toString(), m_session->value("port", 33034).toInt());
}

void AuthDialog::connectionTimeout()
{
    unblockInterface();
    QMessageBox::warning(this, "Error", "Server doesn't respond!", QMessageBox::Ok);
    m_socket->close();
}
