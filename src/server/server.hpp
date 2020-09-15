#ifndef SERVER_HPP
#define SERVER_HPP

#include "asp.hpp"
#include "room/room.hpp"
#include "session/session.hpp"

namespace chat {
class server {
 public:
  server(io::io_context& io_context, std::uint16_t port);

  void async_accept();

 private:
  io::io_context& io_context;
  tcp::acceptor acceptor;
  room chat_room;
};

}  // namespace chat

#endif /* SERVER_HPP */
