#ifndef SERVER_HPP
#define SERVER_HPP

#include "asp.hpp"

namespace chat {
class server {
 public:
  server(io::io_context& io_context, std::uint16_t port);


 private:
  io::io_context& io_context;
  tcp::acceptor acceptor;
};
}  // namespace chat

#endif /* SERVER_HPP */
