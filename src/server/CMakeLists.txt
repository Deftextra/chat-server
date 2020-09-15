project(server)

set(SOURCE_FILES
    server.cpp
    server.hpp
    session/session.cpp
    session/session.hpp
    room/room.cpp
    room/room.hpp
)

set(HEADER_FILES
    server.hpp
    session/session.hpp
    room/room.hpp
    participant/participant.hpp
)

add_library(server STATIC ${SOURCE_FILES})

target_link_libraries(server ${CMAKE_THREAD_LIBS_INIT} )

install(TARGETS server DESTINATION ${CHAT_INSTALL_LIB_DIR})
install(FILES ${HEADER_FILES} DESTINATION ${CHAT_SERVER_INSTALL_INCLUDE_DIR})


