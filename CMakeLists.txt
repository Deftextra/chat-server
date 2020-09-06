cmake_minimum_required(VERSION 3.2)
project(chat-server) 

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

find_package(Threads)

set(CHAT_SERVER_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(CHAT_SERVER_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)

include_directories(${CHAT_SERVER_INSTALL_INCLUDE_DIR})
add_subdirectory(src)
