#include "protocol.h"

//bad news that we will fault if stream.status is not ok because
//we hadn't any chance to notice about it through constructor
//what about exception throwing?

bool ChatMessageBody::pack(QDataStream &stream) const
{
    if(stream.status() != QDataStream::Ok)
        return false;
    return true;
}

bool ChatMessageBody::unpack(QDataStream &stream)
{
    if(stream.status() != QDataStream::Ok)
        return false;
    return true;
}

ChatMessageHeader::ChatMessageHeader(const ChatMessageBody *msgBody)
{
    messageType = msgBody->messageType;
    messageSize = sizeof(*msgBody);
}

ChatMessageHeader::ChatMessageHeader(QDataStream &stream)
{
    unpack(stream);
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

bool AuthorizationAnswer::unpack(QDataStream &stream)
{
    if (stream.status() != QDataStream::Ok)
        return false;
    QByteArray array;
    stream >> authorizationResult >> array;
    denialReason = array;
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

}

bool AuthorizationRequest::pack(QDataStream &stream) const
{
    if (stream.status() != QDataStream::Ok)
        return false;
    stream << username.toUtf8() << password.toUtf8();
    return true;
}

RegistrationRequest::RegistrationRequest()
{
    messageType = mtRegistrationRequest;
}

bool RegistrationRequest::pack(QDataStream &stream) const
{
    if (stream.status() != QDataStream::Ok)
        return false;
    stream << username.toUtf8() << password.toUtf8();
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

bool RegistrationAnswer::unpack(QDataStream &stream)
{
    if (stream.status() != QDataStream::Ok)
        return false;
    QByteArray array;
    stream >> registrationResult >> array;
    denialReason = array;
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

bool StartInfoAnswer::unpack(QDataStream &stream)
{
    if(stream.status() != QDataStream::Ok)
        return false;
    QList<QByteArray> foldersList;
    QList<QByteArray> filesList;
    stream >> foldersList >> filesList >> rights;
    for(int i = 0; foldersList.size(); i++)
        folders.append(QString(foldersList.value(i)));
    for(int i = 0; filesList.size(); i++)
        files.append(QString(filesList.value(i)));
    return true;
}


FolderContentsRequest::FolderContentsRequest()
{
    messageType = mtFolderContentsRequest;
}

bool FolderContentsRequest::pack(QDataStream &stream) const
{
    if(stream.status() != QDataStream::Ok)
        return false;
    stream << path;
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

TransferInfo::TransferInfo()
{
    messageType = mtTransferInfo;
}

TransferInfo::TransferInfo(QDataStream &stream)
{
    messageType = mtTransferInfo;
    unpack(stream);
}

bool TransferInfo::pack(QDataStream &stream) const
{
    if(stream.status() != QDataStream::Ok)
        return false;
    stream  << filesNumber << filesSize << key.toUtf8();
    return true;
}

bool TransferInfo::unpack(QDataStream &stream)
{
    if(stream.status() != QDataStream::Ok)
        return false;
    QByteArray array;
    stream >> filesNumber >> filesSize >> array;
    key = array;
    return true;
}

FileInfo::FileInfo()
{
    messageType = mtFileInfo;
}

bool FileInfo::pack(QDataStream &stream) const
{
    if(stream.status() != QDataStream::Ok)
        return false;
    stream << path.toUtf8()  << fileName.toUtf8() << fileSize;
    return true;
}

bool FileInfo::unpack(QDataStream &stream)
{
    if(stream.status() != QDataStream::Ok)
        return false;
    QByteArray array1;
    QByteArray array2;
    stream >> array1 >> array2 >> fileSize;
    path = array1;
    fileName = array2;
    return true;
}


ActionWithFileRequest::ActionWithFileRequest()
{
    messageType = mtActionWithFileRequest;
}

bool ActionWithFileRequest::pack(QDataStream &stream) const
{
    if(stream.status() != QDataStream::Ok)
        return false;
    stream << actionType  << fileName.toUtf8();
    return true;
}

ActionWithFileAnswer::ActionWithFileAnswer()
{
    messageType = mtActionWithFileAnswer;
}

ActionWithFileAnswer::ActionWithFileAnswer(QDataStream &stream)
{
    messageType = mtActionWithFileAnswer;
    unpack(stream);
}

bool ActionWithFileAnswer::unpack(QDataStream &stream)
{
    if(stream.status() != QDataStream::Ok)
        return false;
    QByteArray array;
    stream >> array >> answer;
    key = array;
    return true;
}
