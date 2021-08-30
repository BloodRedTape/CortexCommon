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
    packet << req.RepositoryName;
    packet << req.FileName;

    return packet;
}

Packet &operator>>(Packet &packet, FileContentRequest &req){
    packet << req.RepositoryName;
    packet >> req.FileName;

    return packet;
}

Packet &operator<<(Packet &packet, const FileContentResponce &res){
    packet << res.RepositoryName;
    packet << res.FileName;
    packet << res.FileContent;

    return packet;
}

Packet &operator>>(Packet &packet, FileContentResponce &res){
    packet >> res.RepositoryName;
    packet >> res.FileName;
    packet >> res.FileContent;

    return packet;
}

Packet &operator<<(Packet &packet, const RepositoryStateNotify &notify){
    packet << notify.RepositoryName;
    packet << notify.RepositoryState;
    return packet;
}

Packet &operator>>(Packet &packet, RepositoryStateNotify &notify){
    packet >> notify.RepositoryName;
    packet >> notify.RepositoryState;
    return packet;
}

Packet &operator<<(Packet &packet, const RepositoriesInfo &info){
    packet << (Uint64)info.RepositoryNames.size();
    for(const auto &name: info.RepositoryNames)
        packet << name;
    return packet;
}

Packet &operator>>(Packet &packet, RepositoriesInfo &info){
    Uint64 size = 0;
    packet >> size;
    info.RepositoryNames.reserve(size);

    for(Uint64 i = 0; i<size; i++){
        std::string filename;
        packet >> filename;
        info.RepositoryNames.emplace_back(std::move(filename));
    }

    return packet;
}