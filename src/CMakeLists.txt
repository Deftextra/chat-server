project(chat)

set(SERVER_SOURCE_FILES main_server.cpp)
set(CLIENT_SOURCE_FILES main_client.cpp)

set(HEADER_FILES asp.hpp)

include_directories(shared)

add_subdirectory(server)
add_subdirectory(client)

add_executable(server_run ${SERVER_SOURCE_FILES})
add_executable(client_run ${CLIENT_SOURCE_FILES}) 

target_link_libraries(server_run ${CMAKE_THREAD_LIBS_INIT} server)
target_link_libraries(client_run ${CMAKE_THREAD_LIBS_INIT} client)


install(TARGETS server_run client_run DESTINATION ${CHAT_SERVER_INSTALL_BIN_DIR})
install(FILES ${HEADER_FILES} DESTINATION ${CHAT_SERVER_INSTALL_INCLUDE_DIR})

