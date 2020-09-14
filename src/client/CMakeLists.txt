project(client)

set(SOURCE_FILES
  client.cpp
  client.hpp
 )
set(HEADER_FILES
  client.hpp
)

add_library(client STATIC ${SOURCE_FILES})
target_link_libraries(client ${CMAKE_THREAD_LIBS_INIT} )

install(TARGETS client DESTINATION ${CHAT_INSTALL_LIB_DIR})
install(FILES ${HEADER_FILES} DESTINATION ${CHAT_SERVER_INSTALL_INCLUDE_DIR})
