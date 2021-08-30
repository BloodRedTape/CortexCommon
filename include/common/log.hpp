#ifndef CORTEX_COMMON_LOG_HPP
#define CORTEX_COMMON_LOG_HPP

#include "fmt/core.h"
#include "fmt/color.h"
#include <utility>

#if defined(CORTEX_SERVER)
    #define CORTEX_TYPE_NAME "Server"
#elif defined(CORTEX_CLIENT)
    #define CORTEX_TYPE_NAME "Client"
#else
    #define CORTEX_TYPE_NAME "Log"
#endif

template<typename ...ArgsType>
inline void Log(const char *fmt, ArgsType&&...args){
    fmt::print("[" CORTEX_TYPE_NAME "]: ");
    fmt::print(fmt, std::forward<ArgsType>(args)...);
    fmt::print("\n");
}

template<typename ...ArgsType>
inline bool Error(const char *fmt, ArgsType&&...args){
    fmt::print(fg(fmt::color::red) | fmt::emphasis::bold, "[Error]: ");
    fmt::print(fg(fmt::color::red) | fmt::emphasis::bold, fmt, std::forward<ArgsType>(args)...);
    fmt::print("\n");
    return false;
}

#endif//CORTEX_COMMON_LOG_HPP