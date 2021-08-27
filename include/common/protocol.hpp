#ifndef CORTEX_COMMON_PROTOCOL_HPP
#define CORTEX_COMMON_PROTOCOL_HPP

#include "common/types.hpp"
#include "common/network.hpp"

constexpr u16 s_DefaultServerPort = 54345;
constexpr u32 s_MagicWord = 0xBBBAADDD;

enum class MsgType: u8{
    Nop = 0,
    Request,
    Result,
    Notification
};

struct Header{
    u32 MagicWord = s_MagicWord;
    MsgType Type = MsgType::Nop;
};

#endif//CORTEX_COMMON_PROTOCOL_HPP