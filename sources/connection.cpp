#include "common/connection.hpp"
#include "common/log.hpp"

void Connection::Send(FileContentRequest req){
    Header header;
    header.MagicWord = s_MagicWord;
    header.Type = MsgType::FileContentRequest;

    m_SendBuffer << header;

    m_SendBuffer << req;

    Status status = send(m_SendBuffer);
    if(status == Done)
        m_SendBuffer.clear();
    else
        OnSendError(status);
}

void Connection::Send(FileContentResponce resp){
    Header header;
    header.MagicWord = s_MagicWord;
    header.Type = MsgType::FileContentResponce;

    m_SendBuffer << header;

    m_SendBuffer << resp;

    Status status = send(m_SendBuffer);
    if(status == Done)
        m_SendBuffer.clear();
    else
        OnSendError(status);
}

void Connection::Send(RepositoryStateNotify notify){
    Header header;
    header.MagicWord = s_MagicWord;
    header.Type = MsgType::RepositoryStateNotify;

    m_SendBuffer << header;

    m_SendBuffer << notify;

    Status status = send(m_SendBuffer);
    if(status == Done)
        m_SendBuffer.clear();
    else
        OnSendError(status);
}

void Connection::Send(RepositoriesInfo info){
    Header header;
    header.MagicWord = s_MagicWord;
    header.Type = MsgType::RepositoriesInfo;

    m_SendBuffer << header;

    m_SendBuffer << info;

    Status status = send(m_SendBuffer);
    if(status == Done)
        m_SendBuffer.clear();
    else
        OnSendError(status);
}

std::string Connection::ToString(){
    return getRemoteAddress().toString() + ":" + std::to_string(getRemotePort());
}

void Connection::OnSendError(Status status){
    Log("Send() failed with status {}, connection address {}", status, ToString());

    m_SendBuffer.clear();
}

