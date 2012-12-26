#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QtDebug>
#include <QDataStream>
#include <QString>
#include <QStringList>
#include <QMap>

enum MessageType
{
    mtUnknown,
    mtAuthorizationRequest,
    mtAuthorizationAnswer,
    mtRegistrationRequest,
    mtRegistrationAnswer,
    mtStartInfoRequest,
    mtStartInfoAnswer,
    mtFolderContentsRequest,
    mtFolderContentsAnswer,
    mtTransferInfo,
    mtFileInfo,
    mtActionWithFileRequest,
    mtActionWithFileAnswer,
    mtCreateFolderMessage,
    mtTransferRejected
    /*etc*/
};

enum ActionType
{
    atDownload,
    atUpload,
    atDelete
};

class MessageBody
{
public:
    MessageBody() {}
    virtual ~MessageBody() {}
    quint8 messageType;
    bool checkStreamState(QDataStream &stream);
    virtual void pack(QDataStream &stream);
    virtual void unpack(QDataStream &stream);
};

class MessageHeader
{
public:
    MessageHeader() {}
    MessageHeader(MessageBody *msgBody);
    MessageHeader(QDataStream &stream);
    quint8 messageType;
    quint32 messageSize;
    bool checkStreamState(QDataStream &stream);
    void pack(QDataStream &stream);
    void unpack(QDataStream &stream);
};

class AuthorizationAnswer: public MessageBody
{
public:
    AuthorizationAnswer();
    AuthorizationAnswer(QDataStream &stream);
    bool authorizationResult;
    QString denialReason;
    void unpack(QDataStream &stream);
};

class AuthorizationRequest: public MessageBody
{
public:
    AuthorizationRequest();
    AuthorizationRequest(QDataStream &stream);
    QString username;
    QString password;
    void pack(QDataStream &stream);
};

class RegistrationRequest: public MessageBody
{
public:
    RegistrationRequest();
    QString username;
    QString password;
    void pack(QDataStream &stream);
};

class RegistrationAnswer: public MessageBody
{
public:
    RegistrationAnswer();
    RegistrationAnswer(QDataStream &stream);
    bool registrationResult;
    QString denialReason;
    void unpack(QDataStream &stream);
};

class StartInfoRequest: public MessageBody
{
public:
    StartInfoRequest();
};

class StartInfoAnswer: public MessageBody
{
public:
    StartInfoAnswer();
    StartInfoAnswer(QDataStream &stream);
    QStringList folders;
    QStringList files;
    quint8 rights;
    void unpack(QDataStream &stream);
};

class FolderContentRequest: public MessageBody
{
public:
    FolderContentRequest();
    QString path;
    void pack(QDataStream &stream);
};

class FolderContentAnswer: public MessageBody
{
public:
    FolderContentAnswer();
    FolderContentAnswer(QDataStream &stream);
    QStringList folders;
    QStringList files;
    void unpack(QDataStream &stream);
};

class TransferInfo: public MessageBody
{
public:
    TransferInfo();
    TransferInfo(QDataStream &stream);
    quint64 filesSize;
    quint32 filesNumber;
    QString key;
    void pack(QDataStream &stream);
    void unpack(QDataStream &stream);
};

class FileInfo: public MessageBody
{
public:
    FileInfo();
    FileInfo(QDataStream &stream);
    QString path;
    QString fileName;
    quint64 fileSize;
    void pack(QDataStream &stream);
    void unpack(QDataStream &stream);
};

class ActionWithFileRequest: public MessageBody
{
public:
    ActionWithFileRequest();
    quint8 actionType;
    QString fileName;
    void pack(QDataStream &stream);
};

class ActionWithFileAnswer: public MessageBody
{
public:
    ActionWithFileAnswer();
    ActionWithFileAnswer(QDataStream &stream);
    QString key;
    bool answer;
    void unpack(QDataStream &stream);
};

class CreateFolderMessage: public MessageBody
{
public:
    CreateFolderMessage();
    CreateFolderMessage(QDataStream &stream);
    QString path;
    QString folderName;
    void pack(QDataStream &stream);
    void unpack(QDataStream &stream);
};

class TransferRejected: public MessageBody
{
public:
    TransferRejected();
    TransferRejected(QDataStream &stream);
    QString message;
    void pack(QDataStream &stream);
    void unpack(QDataStream &stream);
};

#endif // PROTOCOL_H
