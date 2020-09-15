#ifndef SESSION_HPP
#define SESSION_HPP

#include <queue>
#include <string>

#include "../participant/participant.hpp"
#include "asp.hpp"

namespace chat {

class session : public std::enable_shared_from_this<session>,
                public participant {
 public:
  session(tcp::socket&& socket);
  void start(message_handler&& on_message, error_handler&& on_error);
  void post(const Message&);
  std::string compose_name();
  std::string compose_body();

 private:
  void async_read_body();
  void on_read_body(const error_code, std::size_t bytes_transferred);
  void async_write_message();
  void on_write_message(error_code error, std::size_t bytes_transferred);
  void query_for_name();
  void on_query_for_name(error_code error, std::size_t bytes_transferred);
  void get_name();
  void on_get_name(error_code error, std::size_t bytes_transferred);

  // Outgoing queue prevents us from a data race by writing into the socket.
  std::queue<Message> outgoing;
  tcp::socket connected_sock;
  io::streambuf body_buff;
  message_handler on_successful_read;
  error_handler on_error;
  std::string name_buff;
};

}  // namespace chat

#endif /* SESSION_HPP */