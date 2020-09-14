#ifndef SESSION_HPP
#define SESSION_HPP

#include <queue>
#include "asp.hpp"
#include "../participant/participant.hpp"

namespace chat {

class session : public std::enable_shared_from_this<session>,
                public participant {
 public:
  session(tcp::socket&& socket);
  void start(message_handler&& on_message, error_handler&& on_error);
  void post(const Message&);

 private:
  void async_read();
  void on_read(const error_code, std::size_t bytes_transferred);
  void async_write();
  void on_write(error_code error, std::size_t bytes_transferred);

    // Outgoing queue prevents us from a data race by writing into the socket.
  std::queue<Message> outgoing;
  tcp::socket connected_sock;
  io::streambuf read_sbuff;
  message_handler on_susccesful_read;
  error_handler on_error;
};

}  // namespace chat

#endif /* SESSION_HPP */