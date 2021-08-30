cmake_minimum_required(VERSION 3.10)


project(CortexCommon)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/filesystem)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/assert)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/config)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/container_hash)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/core)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/detail)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/preprocessor)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/static_assert)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/io)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/iterator)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/range)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/smart_ptr)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/system)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/type_traits)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/integer)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/throw_exception)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/concept_check)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/conversion)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/move)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/typeof)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/function_types)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/mpl)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/predef)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/utility)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/fusion)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/tuple)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/optional)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/winapi)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/atomic)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/align)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/array)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/regex)

set(SFML_BUILD_WINDOW FALSE)
set(SFML_BUILD_GRAPHICS FALSE)
set(SFML_BUILD_AUDIO FALSE)
set(SFML_BUILD_NETWORK TRUE)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/SFML)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/yaml-cpp)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/fmt)

set(CORTEX_COMMON_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/repository.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/protocol.cpp
)

add_library(CortexCommon STATIC 
    ${CORTEX_COMMON_SOURCES}
)

target_include_directories(CortexCommon PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/sources
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/SFML/include
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/filesystem/include
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/yaml-cpp/include
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/fmt/include
)

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

target_link_libraries(CortexCommon
    sfml-system
    sfml-network

    Boost::filesystem
    Boost::assert
    Boost::config
    Boost::container_hash
    Boost::core
    Boost::detail
    Boost::preprocessor
    Boost::static_assert
    Boost::io
    Boost::iterator
    Boost::range
    Boost::smart_ptr
    Boost::system
    Boost::type_traits
    Boost::integer
    Boost::throw_exception
    Boost::concept_check
    Boost::conversion
    Boost::move
    Boost::typeof
    Boost::function_types
    Boost::mpl
    Boost::predef
    Boost::utility
    Boost::fusion
    Boost::tuple
    Boost::optional
    Boost::winapi
    Boost::atomic
    Boost::align
    Boost::array
    Boost::regex

    yaml-cpp
    fmt
)