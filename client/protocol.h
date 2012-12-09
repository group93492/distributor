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
    mtFolderContentsAnswer
    /*etc*/
};

class ChatMessageBody
{
public:
    ChatMessageBody() {}
    virtual ~ChatMessageBody() {}
    quint8 messageType;
    virtual bool pack(QDataStream &stream) const = 0;
    virtual bool unpack(QDataStream &stream) = 0;
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

class AuthorizationAnswer : public ChatMessageBody
{
public:
    AuthorizationAnswer();
    AuthorizationAnswer(QDataStream &stream);
    bool authorizationResult;
    QString denialReason;
    bool pack(QDataStream &stream) const;
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
    bool unpack(QDataStream &stream);
};

class RegistrationRequest: public ChatMessageBody
{
public:
    RegistrationRequest();
    RegistrationRequest(QDataStream &stream);
    QString username;
    QString password;
    bool pack(QDataStream &stream) const;
    bool unpack(QDataStream &stream);
};

class RegistrationAnswer: public ChatMessageBody
{
public:
    RegistrationAnswer();
    RegistrationAnswer(QDataStream &stream);
    bool registrationResult;
    QString denialReason;
    bool pack(QDataStream &stream) const;
    bool unpack(QDataStream &stream);
};

class StartInfoRequest: public ChatMessageBody
{
public:
    StartInfoRequest();
    QString nickname;
    bool pack(QDataStream &stream) const;
    bool unpack(QDataStream &stream);
};

class StartInfoAnswer: public ChatMessageBody
{
public:
    StartInfoAnswer();
    StartInfoAnswer(QDataStream &stream);
    QStringList folders;
    QStringList files;
    QString rights;
    bool pack(QDataStream &stream) const;
    bool unpack(QDataStream &stream);
};

class FolderContentsRequest: public ChatMessageBody
{
public:
    FolderContentsRequest();
    FolderContentsRequest(QDataStream &stream);
    QString path;
    bool pack(QDataStream &stream) const;
    bool unpack(QDataStream &stream);
};

class FolderContentsAnswer: public ChatMessageBody
{
public:
    FolderContentsAnswer();
    FolderContentsAnswer(QDataStream &stream);
    QStringList folders;
    QStringList files;
    bool pack(QDataStream &stream) const;
    bool unpack(QDataStream &stream);
};

#endif // PROTOCOL_H
