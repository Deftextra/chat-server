project(client)

set(SOURCE_FILES
  client.cpp
  )

add_executable(client ${SOURCE_FILES}) 
target_link_libraries(client ${CMAKE_THREAD_LIBS_INIT} )
install(TARGETS client DESTINATION ${HTTPSERVER_INSTALL_BIN_DIR})

