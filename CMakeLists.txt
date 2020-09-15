cmake_minimum_required(VERSION 3.2)
project(chat-server) 

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O3")
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

find_package(Threads)

set(CHAT_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)
set(CHAT_SERVER_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(CHAT_SERVER_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(SERVER_HEADERS_DIR ${PROJECT_SOURCE_DIR}/src/server)

# TODO: Set server and client header directories
#       for external use.

include_directories(${CHAT_SERVER_INSTALL_INCLUDE_DIR})
include_directories(${SERVER_HEADERS_DIR})

add_subdirectory(src)
