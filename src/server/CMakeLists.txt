project(server)


set(SOURCE_FILES
  server.cpp
  )

add_executable(server ${SOURCE_FILES})
install(TARGETS server DESTINATION ${HTTPSERVER_INSTALL_BIN_DIR})



