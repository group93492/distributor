#ifndef PROTOCOL_H
#define PROTOCOL_H

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
    mtCreateFolderMessage
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
    virtual bool pack(QDataStream &stream) const;
    virtual bool unpack(QDataStream &stream);
};

class MessageHeader
{
public:
    MessageHeader() {}
    MessageHeader(const MessageBody *msgBody);
    MessageHeader(QDataStream &stream);
    quint8 messageType;
    quint32 messageSize;
    bool pack(QDataStream &stream) const;
    bool unpack(QDataStream &stream);
};

class AuthorizationAnswer: public MessageBody
{
public:
    AuthorizationAnswer();
    AuthorizationAnswer(QDataStream &stream);
    bool authorizationResult;
    QString denialReason;
    bool unpack(QDataStream &stream);
};

class AuthorizationRequest: public MessageBody
{
public:
    AuthorizationRequest();
    AuthorizationRequest(QDataStream &stream);
    QString username;
    QString password;
    bool pack(QDataStream &stream) const;
};

class RegistrationRequest: public MessageBody
{
public:
    RegistrationRequest();
    QString username;
    QString password;
    bool pack(QDataStream &stream) const;
};

class RegistrationAnswer: public MessageBody
{
public:
    RegistrationAnswer();
    RegistrationAnswer(QDataStream &stream);
    bool registrationResult;
    QString denialReason;
    bool unpack(QDataStream &stream);
};

class StartInfoRequest: public MessageBody
{
public:
    StartInfoRequest();
    bool pack(QDataStream &stream) const;
};

class StartInfoAnswer: public MessageBody
{
public:
    StartInfoAnswer();
    StartInfoAnswer(QDataStream &stream);
    QStringList folders;
    QStringList files;
    quint8 rights;
    bool unpack(QDataStream &stream);
};

class FolderContentsRequest: public MessageBody
{
public:
    FolderContentsRequest();
    QString path;
    bool pack(QDataStream &stream) const;
};

class FolderContentsAnswer: public MessageBody
{
public:
    FolderContentsAnswer();
    FolderContentsAnswer(QDataStream &stream);
    QStringList folders;
    QStringList files;
    bool unpack(QDataStream &stream);
};

class TransferInfo: public MessageBody
{
public:
    TransferInfo();
    TransferInfo(QDataStream &stream);
    quint64 filesSize;
    quint32 filesNumber;
    QString key;
    bool pack(QDataStream &stream) const;
    bool unpack(QDataStream &stream);
};

class FileInfo: public MessageBody
{
public:
    FileInfo();
    FileInfo(QDataStream &stream);
    QString path;
    QString fileName;
    quint64 fileSize;
    bool pack(QDataStream &stream) const;
    bool unpack(QDataStream &stream);
};

class ActionWithFileRequest: public MessageBody
{
public:
    ActionWithFileRequest();
    quint8 actionType;
    QString fileName;
    bool pack(QDataStream &stream) const;
};

class ActionWithFileAnswer: public MessageBody
{
public:
    ActionWithFileAnswer();
    ActionWithFileAnswer(QDataStream &stream);
    QString key;
    bool answer;
    bool unpack(QDataStream &stream);
};

class CreateFolderMessage: public MessageBody
{
public:
    CreateFolderMessage();
    CreateFolderMessage(QDataStream &stream);
    QString path;
    QString folderName;
    bool pack(QDataStream &stream) const;
    bool unpack(QDataStream &stream);
};

#endif // PROTOCOL_H
