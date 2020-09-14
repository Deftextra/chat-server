#include "session.hpp"

chat::session::session(tcp::socket&& socket)
    : connected_sock{std::move(socket)} {}

void chat::session::start(message_handler&& on_message,
                          error_handler&& on_error) {
  this->on_susccesful_read = std::move(on_message);
  this->on_error = std::move(on_error);
  async_read();
}

void chat::session::post(const Message& message) {
  bool is_not_posting = outgoing.empty();

  if (is_not_posting) {
    outgoing.push(message);
    async_write();
  }
}

void chat::session::async_read() {
  io::async_read_until(connected_sock, read_sbuff, "\nEOF",
                       [self = shared_from_this()](
                           error_code error, std::size_t bytes_transferred) {
                         self->on_read(error, bytes_transferred);
                       });
}

void chat::session::on_read(error_code error, std::size_t bytes_transferred) {
  if (!error) {
    std::stringstream message;
    message << connected_sock.remote_endpoint(error) << ": "
            << std::istream(&read_sbuff).rdbuf();
    read_sbuff.consume(bytes_transferred);
    // TODO: Inside the completion handeler (on_succefull_read) we want to 
    // add the message to the chat room and deliver to all connected clients.
    on_susccesful_read(message.str());
    async_read();
  } else {
    connected_sock.close(error);
    on_error();
  }
}

void chat::session::async_write() {
    //TODO: compose a more useful message
  std::array<io::const_buffer, 2> view{io::buffer(outgoing.front().getName()),
                                       io::buffer(outgoing.front().getBody())};

  io::async_write(connected_sock, view,
                  [self = shared_from_this()](error_code error,
                                              std::size_t bytes_transferred) {
                    self->on_write(error, bytes_transferred);
                  });
}

void chat::session::on_write(error_code error, std::size_t bytes_transferred) {
  if (!error) {
    outgoing.pop();

    if (!outgoing.empty()) {
      async_write();
    }
  } 
  else {
    connected_sock.close(error);
    on_error();
  }
}
