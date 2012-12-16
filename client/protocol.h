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
    mtActionWithFileAnswer
    /*etc*/
};

class ChatMessageBody
{
public:
    ChatMessageBody() {}
    virtual ~ChatMessageBody() {}
    quint8 messageType;
    virtual bool pack(QDataStream &stream) const;
    virtual bool unpack(QDataStream &stream);
};

class ChatMessageHeader
{
public:
    ChatMessageHeader() {}
    ChatMessageHeader(const ChatMessageBody *msgBody);
    ChatMessageHeader(QDataStream &stream);
    quint8 messageType;
    quint32 messageSize;
    bool pack(QDataStream &stream) const;
    bool unpack(QDataStream &stream);
};

class AuthorizationAnswer: public ChatMessageBody
{
public:
    AuthorizationAnswer();
    AuthorizationAnswer(QDataStream &stream);
    bool authorizationResult;
    QString denialReason;
    bool unpack(QDataStream &stream);
};

class AuthorizationRequest: public ChatMessageBody
{
public:
    AuthorizationRequest();
    AuthorizationRequest(QDataStream &stream);
    QString username;
    QString password;
    bool pack(QDataStream &stream) const;
};

class RegistrationRequest: public ChatMessageBody
{
public:
    RegistrationRequest();
    QString username;
    QString password;
    bool pack(QDataStream &stream) const;
};

class RegistrationAnswer: public ChatMessageBody
{
public:
    RegistrationAnswer();
    RegistrationAnswer(QDataStream &stream);
    bool registrationResult;
    QString denialReason;
    bool unpack(QDataStream &stream);
};

class StartInfoRequest: public ChatMessageBody
{
public:
    StartInfoRequest();
    bool pack(QDataStream &stream) const;
};

class StartInfoAnswer: public ChatMessageBody
{
public:
    StartInfoAnswer();
    StartInfoAnswer(QDataStream &stream);
    QStringList folders;
    QStringList files;
    quint8 rights;
    bool unpack(QDataStream &stream);
};

class FolderContentsRequest: public ChatMessageBody
{
public:
    FolderContentsRequest();
    QString path;
    bool pack(QDataStream &stream) const;
};

class FolderContentsAnswer: public ChatMessageBody
{
public:
    FolderContentsAnswer();
    FolderContentsAnswer(QDataStream &stream);
    QStringList folders;
    QStringList files;
    bool unpack(QDataStream &stream);
};

class TransferInfo: public ChatMessageBody
{
public:
    TransferInfo();
    TransferInfo(QDataStream &stream);
    qint64 filesSize;
    quint32 filesNumber;
    QString key;
    bool pack(QDataStream &stream) const;
    bool unpack(QDataStream &stream);
};

class FileInfo: public ChatMessageBody
{
public:
    FileInfo();
    FileInfo(QDataStream &stream);
    QString path;
    QString fileName;
    qint64 fileSize;
    bool pack(QDataStream &stream) const;
    bool unpack(QDataStream &stream);
};

class ActionWithFileRequest: public ChatMessageBody
{
public:
    ActionWithFileRequest();
    quint8 actionType;
    QString fileName;
    bool pack(QDataStream &stream) const;
};

class ActionWithFileAnswer : public ChatMessageBody
{
public:
    ActionWithFileAnswer();
    ActionWithFileAnswer(QDataStream &stream);
    QString key;
    bool unpack(QDataStream &stream);
};

#endif // PROTOCOL_H
