#ifndef CORTEX_COMMON_PROTOCOL_HPP
#define CORTEX_COMMON_PROTOCOL_HPP

#include <string>
#include "common/types.hpp"
#include "common/network.hpp"
#include "common/repository.hpp"

constexpr u16 s_DefaultServerPort = 54346;
constexpr u32 s_MagicWord = 0xBBBAADDD;

enum class MsgType: u8{
    Nop = 0,
    FileContentRequest,
    FileContentResponce,
    RepositoryStateNotify,
    RepositoriesInfo
};

struct Header{
    u32 MagicWord = s_MagicWord;
    MsgType Type = MsgType::Nop;

    friend Packet &operator<<(Packet &packet, const Header &header);

    friend Packet &operator>>(Packet &packet, Header &header);
};

struct FileContentRequest{
    std::string RepositoryName;
    std::string FileName;

    friend Packet &operator<<(Packet &packet, const FileContentRequest &header);

    friend Packet &operator>>(Packet &packet, FileContentRequest &header);
};

struct FileContentResponce{
    std::string RepositoryName;
    std::string FileName;
    std::string FileContent;

    friend Packet &operator<<(Packet &packet, const FileContentResponce &header);

    friend Packet &operator>>(Packet &packet, FileContentResponce &header);
};

struct RepositoryStateNotify{
    std::string RepositoryName;
    struct RepositoryState RepositoryState;

    friend Packet &operator<<(Packet &packet, const RepositoryStateNotify &header);

    friend Packet &operator>>(Packet &packet, RepositoryStateNotify &header);
};

struct RepositoriesInfo{
    std::vector<RepositoryStateNotify> Repositories;

    friend Packet &operator<<(Packet &packet, const RepositoriesInfo &info);

    friend Packet &operator>>(Packet &packet, RepositoriesInfo &info);
};

#endif//CORTEX_COMMON_PROTOCOL_HPP