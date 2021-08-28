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

Packet &operator<<(Packet &packet, const FileContentRequest &header){
    packet << header.Name;

    return packet;
}

Packet &operator>>(Packet &packet, FileContentRequest &header){
    packet >> header.Name;

    return packet;
}

Packet &operator<<(Packet &packet, const FileContentResponce &header){
    packet << header.Name;
    packet << header.Content;

    return packet;
}

Packet &operator>>(Packet &packet, FileContentResponce &header){
    packet >> header.Name;
    packet >> header.Content;

    return packet;
}

Packet &operator<<(Packet &packet, const RepositoryStateNotify &header){
    packet << header.State;
    return packet;
}

Packet &operator>>(Packet &packet, RepositoryStateNotify &header){
    packet >> header.State;
    return packet;
}