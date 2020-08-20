project(client)

set(SOURCE_FILES
  client.cpp
  )

add_executable(client ${SOURCE_FILES}) 
install(TARGETS client DESTINATION ${HTTPSERVER_INSTALL_BIN_DIR})

