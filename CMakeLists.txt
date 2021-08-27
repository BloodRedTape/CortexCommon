cmake_minimum_required(VERSION 3.10)


project(CortexCommon)

set(CORTEX_COMMON_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/repository.cpp
)

add_library(CortexCommon STATIC 
    ${CORTEX_COMMON_SOURCES}
)

target_include_directories(CortexCommon PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/sources
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)