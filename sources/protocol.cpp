#include "common/protocol.hpp"

Packet &operator<<(Packet &packet, const Header &header){
    packet << header.MagicWord;
    packet << (u8)header.Type;

    return packet;
}

Packet &operator>>(Packet &packet, Header &header){
    packet >> header.MagicWord;
    packet >> (u8&)header.Type;

    return packet;
}

Packet &operator<<(Packet &packet, const FileContentRequest &req){
    packet << req.Name;

    return packet;
}

Packet &operator>>(Packet &packet, FileContentRequest &req){
    packet >> req.Name;

    return packet;
}

Packet &operator<<(Packet &packet, const FileContentResponce &res){
    packet << res.Name;
    packet << res.Content;

    return packet;
}

Packet &operator>>(Packet &packet, FileContentResponce &res){
    packet >> res.Name;
    packet >> res.Content;

    return packet;
}

Packet &operator<<(Packet &packet, const RepositoryStateNotify &notify){
    packet << notify.Name;
    packet << notify.State;
    return packet;
}

Packet &operator>>(Packet &packet, RepositoryStateNotify &notify){
    packet >> notify.Name;
    packet >> notify.State;
    return packet;
}