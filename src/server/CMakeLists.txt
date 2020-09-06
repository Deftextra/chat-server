project(server)


set(SOURCE_FILES
  server.cpp
  )

add_executable(server ${SOURCE_FILES})
target_link_libraries(server ${CMAKE_THREAD_LIBS_INIT} )
install(TARGETS server DESTINATION ${CHAT_SERVER_INSTALL_BIN_DIR})



