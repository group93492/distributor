#include "protocol.h"

ChatMessageHeader::ChatMessageHeader(const ChatMessageBody *msgBody)
{
    messageType = msgBody->messageType;
    messageSize = sizeof(*msgBody);
}

ChatMessageHeader::ChatMessageHeader(QDataStream &stream)
{
    unpack(stream);
    //bad news that we will fault if stream.status is not ok because
    //we hadn't any chance to notice about it through constructor
}

bool ChatMessageHeader::pack(QDataStream &stream) const
{
    if (stream.status() != QDataStream::Ok)
        return false;
    stream << messageType;
    return true;
}

bool ChatMessageHeader::unpack(QDataStream &stream)
{
    if (stream.status() != QDataStream::Ok)
        return false;
    stream >> messageType;
    return true;
}

AuthorizationAnswer::AuthorizationAnswer()
{
    messageType = mtAuthorizationAnswer;
}

AuthorizationAnswer::AuthorizationAnswer(QDataStream &stream)
{
    messageType = mtAuthorizationAnswer;
    unpack(stream);
    //bad news that we will fault if stream.status is not ok because
    //we hadn't any chance to notice about it through constructor
}

bool AuthorizationAnswer::pack(QDataStream &stream) const
{
    if (stream.status() != QDataStream::Ok)
        return false;
    if(authorizationResult)
        stream << authorizationResult;
    else
        stream << authorizationResult << denialReason.toUtf8();
    return true;
}

bool AuthorizationAnswer::unpack(QDataStream &stream)
{
    if (stream.status() != QDataStream::Ok)
        return false;
    return true;
}

AuthorizationRequest::AuthorizationRequest()
{
    messageType = mtAuthorizationRequest;
}

AuthorizationRequest::AuthorizationRequest(QDataStream &stream)
{
    messageType = mtAuthorizationRequest;
    unpack(stream);
    //bad news that we will fault if stream.status is not ok because
    //we hadn't any chance to notice about it through constructor
    //what about exception throwing?
}

bool AuthorizationRequest::pack(QDataStream &stream) const
{
    if (stream.status() != QDataStream::Ok)
        return false;
    stream << username.toUtf8() << password.toUtf8();
    return true;
}

bool AuthorizationRequest::unpack(QDataStream &stream)
{
    if (stream.status() != QDataStream::Ok)
        return false;
    return true;
}

RegistrationRequest::RegistrationRequest()
{
    messageType = mtRegistrationRequest;
}

RegistrationRequest::RegistrationRequest(QDataStream &stream)
{
    messageType = mtRegistrationRequest;
    unpack(stream);
}

bool RegistrationRequest::pack(QDataStream &stream) const
{
    if (stream.status() != QDataStream::Ok)
        return false;
    stream << username.toUtf8() << password.toUtf8();
    return true;
}

bool RegistrationRequest::unpack(QDataStream &stream)
{
    if (stream.status() != QDataStream::Ok)
        return false;
    return true;
}

RegistrationAnswer::RegistrationAnswer()
{
    messageType = mtRegistrationAnswer;
}

RegistrationAnswer::RegistrationAnswer(QDataStream &stream)
{
    messageType = mtRegistrationAnswer;
    unpack(stream);
}

bool RegistrationAnswer::pack(QDataStream &stream) const
{
    if (stream.status() != QDataStream::Ok)
        return false;
    return true;
}

bool RegistrationAnswer::unpack(QDataStream &stream)
{
    if (stream.status() != QDataStream::Ok)
        return false;
    stream >> registrationResult;
    if(!registrationResult)
    {
        QByteArray array;
        stream >> array;
        denialReason = array;
    }
    return true;
}

StartInfoRequest::StartInfoRequest()
{
    messageType = mtStartInfoRequest;
}

bool StartInfoRequest::pack(QDataStream &stream) const
{
    if(stream.status() != QDataStream::Ok)
        return false;
    stream << nickname.toUtf8();
    return true;
}

bool StartInfoRequest::unpack(QDataStream &stream)
{
    if(stream.status() != QDataStream::Ok)
        return false;
    return true;
}


StartInfoAnswer::StartInfoAnswer()
{
    messageType = mtStartInfoAnswer;
}

StartInfoAnswer::StartInfoAnswer(QDataStream &stream)
{
    messageType = mtStartInfoAnswer;
    unpack(stream);
}

bool StartInfoAnswer::pack(QDataStream &stream) const
{
    if(stream.status() != QDataStream::Ok)
        return false;
    return true;
}

bool StartInfoAnswer::unpack(QDataStream &stream)
{
    if(stream.status() != QDataStream::Ok)
        return false;
    QList<QByteArray> foldersList;
    QList<QByteArray> filesList;
    QByteArray array;
    stream >> foldersList >> filesList >> array;
    for(int i = 0; foldersList.size(); i++)
        folders.append(QString(foldersList.value(i)));
    for(int i = 0; filesList.size(); i++)
        files.append(QString(filesList.value(i)));
    rights = array;
    return true;
}


FolderContentsRequest::FolderContentsRequest()
{
    messageType = mtFolderContentsRequest;
}

FolderContentsRequest::FolderContentsRequest(QDataStream &stream)
{
    messageType = mtFolderContentsRequest;
    unpack(stream);
}

bool FolderContentsRequest::pack(QDataStream &stream) const
{
    if(stream.status() != QDataStream::Ok)
        return false;
    stream << path;
    return true;
}

bool FolderContentsRequest::unpack(QDataStream &stream)
{
    if(stream.status() != QDataStream::Ok)
        return false;
    return true;
}

FolderContentsAnswer::FolderContentsAnswer()
{
    messageType = mtFolderContentsAnswer;
}

FolderContentsAnswer::FolderContentsAnswer(QDataStream &stream)
{
    messageType = mtFolderContentsAnswer;
    unpack(stream);
}

bool FolderContentsAnswer::pack(QDataStream &stream) const
{
    if(stream.status() != QDataStream::Ok)
        return false;
    return true;
}

bool FolderContentsAnswer::unpack(QDataStream &stream)
{
    if(stream.status() != QDataStream::Ok)
        return false;
    QList<QByteArray> foldersList;
    QList<QByteArray> filesList;
    stream >> foldersList >> filesList;
    for(int i = 0; foldersList.size(); i++)
        folders.append(QString(foldersList.value(i)));
    for(int i = 0; filesList.size(); i++)
        files.append(QString(filesList.value(i)));
    return true;
}
