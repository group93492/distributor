#include "protocol.h"

bool MessageBody::checkStreamState(QDataStream &stream)
{
    if(stream.status() != QDataStream::Ok)
    {
        stream.device()->readAll().clear();
        qDebug() << "Stream is not ready, clear all data in socket!";
        return false;
    }
    return true;
}

void MessageBody::pack(QDataStream &stream)
{
}

void MessageBody::unpack(QDataStream &stream)
{
}

MessageHeader::MessageHeader(MessageBody *msgBody)
{
    messageType = msgBody->messageType;
    messageSize = sizeof(*msgBody);
}

MessageHeader::MessageHeader(QDataStream &stream)
{
    unpack(stream);
}

bool MessageHeader::checkStreamState(QDataStream &stream)
{
    if(stream.status() != QDataStream::Ok)
    {
        stream.device()->readAll().clear();
        qDebug() << "Stream is not ready, clear all data in socket!";
        return false;
    }
    return true;
}

void MessageHeader::pack(QDataStream &stream)
{
    if(!checkStreamState(stream))
        return;
    stream << messageType;
}

void MessageHeader::unpack(QDataStream &stream)
{
    if(!checkStreamState(stream))
        return;
    stream >> messageType;
}

AuthorizationAnswer::AuthorizationAnswer()
{
    messageType = mtAuthorizationAnswer;
}

AuthorizationAnswer::AuthorizationAnswer(QDataStream &stream)
{
    messageType = mtAuthorizationAnswer;
    unpack(stream);
}

void AuthorizationAnswer::unpack(QDataStream &stream)
{
    if(!checkStreamState(stream))
        return;
    QByteArray array;
    stream >> authorizationResult >> array;
    denialReason = array;
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

void AuthorizationRequest::pack(QDataStream &stream)
{
    if(!checkStreamState(stream))
        return;
    stream << username.toUtf8() << password.toUtf8();
}

RegistrationRequest::RegistrationRequest()
{
    messageType = mtRegistrationRequest;
}

void RegistrationRequest::pack(QDataStream &stream)
{
    if(!checkStreamState(stream))
        return;
    stream << username.toUtf8() << password.toUtf8();
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

void RegistrationAnswer::unpack(QDataStream &stream)
{
    if(!checkStreamState(stream))
        return;
    QByteArray array;
    stream >> registrationResult >> array;
    denialReason = array;
}

StartInfoRequest::StartInfoRequest()
{
    messageType = mtStartInfoRequest;
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

void StartInfoAnswer::unpack(QDataStream &stream)
{
    if(!checkStreamState(stream))
        return;
    QList<QByteArray> foldersList;
    QList<QByteArray> filesList;
    stream >> foldersList >> filesList >> rights;
    for(int i = 0; foldersList.size(); i++)
        folders.append(QString(foldersList.value(i)));
    for(int i = 0; filesList.size(); i++)
        files.append(QString(filesList.value(i)));
}


FolderContentRequest::FolderContentRequest()
{
    messageType = mtFolderContentsRequest;
}

void FolderContentRequest::pack(QDataStream &stream)
{
    if(!checkStreamState(stream))
        return;
    stream << path;
}

FolderContentAnswer::FolderContentAnswer()
{
    messageType = mtFolderContentsAnswer;
}

FolderContentAnswer::FolderContentAnswer(QDataStream &stream)
{
    messageType = mtFolderContentsAnswer;
    unpack(stream);
}

void FolderContentAnswer::unpack(QDataStream &stream)
{
    if(!checkStreamState(stream))
        return;
    QList<QByteArray> foldersList;
    QList<QByteArray> filesList;
    stream >> foldersList >> filesList;
    for(int i = 0; foldersList.size(); i++)
        folders.append(QString(foldersList.value(i)));
    for(int i = 0; filesList.size(); i++)
        files.append(QString(filesList.value(i)));
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

void TransferInfo::pack(QDataStream &stream)
{
    if(!checkStreamState(stream))
        return;
    stream  << filesNumber << filesSize << key.toUtf8();
}

void TransferInfo::unpack(QDataStream &stream)
{
    if(!checkStreamState(stream))
        return;
    QByteArray array;
    stream >> filesNumber >> filesSize >> array;
    key = array;
}

FileInfo::FileInfo()
{
    messageType = mtFileInfo;
}

void FileInfo::pack(QDataStream &stream)
{
    if(!checkStreamState(stream))
        return;
    stream << path.toUtf8()  << fileName.toUtf8() << fileSize;
}

void FileInfo::unpack(QDataStream &stream)
{
    if(!checkStreamState(stream))
        return;
    QByteArray array1;
    QByteArray array2;
    stream >> array1 >> array2 >> fileSize;
    path = array1;
    fileName = array2;
}


ActionWithFileRequest::ActionWithFileRequest()
{
    messageType = mtActionWithFileRequest;
}

void ActionWithFileRequest::pack(QDataStream &stream)
{
    if(!checkStreamState(stream))
        return;
    stream << actionType  << fileName.toUtf8();
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

void ActionWithFileAnswer::unpack(QDataStream &stream)
{
    if(!checkStreamState(stream))
        return;
    QByteArray array;
    stream >> array >> answer;
    key = array;
}

CreateFolderMessage::CreateFolderMessage()
{
    messageType = mtCreateFolderMessage;
}

CreateFolderMessage::CreateFolderMessage(QDataStream &stream)
{
    messageType = mtCreateFolderMessage;
    unpack(stream);
}

void CreateFolderMessage::pack(QDataStream &stream)
{
    if(!checkStreamState(stream))
        return;
    stream << path.toUtf8() << folderName.toUtf8();
}

void CreateFolderMessage::unpack(QDataStream &stream)
{
    if(!checkStreamState(stream))
        return;
    QByteArray array1;
    QByteArray array2;
    stream >> array1 >> array2;
    path = array1;
    folderName = array2;
}

TransferRejected::TransferRejected()
{
    messageType = mtTransferRejected;
}

TransferRejected::TransferRejected(QDataStream &stream)
{
    messageType = mtTransferRejected;
    unpack(stream);
}

void TransferRejected::pack(QDataStream &stream)
{
    if(!checkStreamState(stream))
        return;
    stream << message.toUtf8();
}

void TransferRejected::unpack(QDataStream &stream)
{
    if(!checkStreamState(stream))
        return;
    QByteArray array;
    stream >> array;
    message = array;
}
