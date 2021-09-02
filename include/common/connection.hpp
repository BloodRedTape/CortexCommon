#ifndef CORTEX_COMMON_CONNECTION_HPP
#define CORTEX_COMMON_CONNECTION_HPP

#include "common/network.hpp"
#include "protocol.hpp"

class Connection: public TcpSocket{
private:
    Packet m_SendBuffer;
public:
    Connection(){
        setBlocking(false);
    }

    Connection(Connection &&) = default;

    Connection &operator=(Connection &&) = default;

    void Send(FileContentRequest req);

    void Send(FileContentResponce resp);

    void Send(RepositoryStateNotify notify);

    void Send(AllRepositoriesStateNotify info);

    std::string ToString();

    void OnSendError(Status status);
};

#endif//CORTEX_COMMON_CONNECTION_HPP