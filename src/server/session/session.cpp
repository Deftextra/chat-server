#include "session.hpp"

chat::session::session(tcp::socket&& socket)
    : connected_sock{std::move(socket)}, body_buff(MAX_BODY_SIZE) {}

void chat::session::start(message_handler&& on_message,
                          error_handler&& on_error) {
  this->on_susccesful_read = std::move(on_message);
  this->on_error = std::move(on_error);

  ask_for_name();
}

void chat::session::ask_for_name() {
  io::async_write(connected_sock, io::buffer("Enter name: "),
                  [self = shared_from_this()](error_code error,
                                              std::size_t bytes_transferred) {
                    self->on_ask_for_name(error, bytes_transferred);
                  });
}

void chat::session::on_ask_for_name(error_code error,
                                    std::size_t bytes_transferred) {
  if (!error) {
    get_name();
  } else {
    connected_sock.close();
    on_error();
  }
}

void chat::session::get_name() {
  io::async_read_until(connected_sock, io::dynamic_buffer(name, MAX_NAME_SIZE),
                       '\n',
                       [self = shared_from_this()](
                           error_code error, std::size_t bytes_transferred) {
                         self->on_get_name(error, bytes_transferred);
                       });
}

void chat::session::on_get_name(error_code error,
                                std::size_t bytes_transferred) {
  if (!error) {
    async_read_body();
  } else {
    if (io::error::not_found == error.value()) {
      // TODO: Add code for to long condition.
    } else {
      connected_sock.close();
      on_error();
    }
  }
}
void chat::session::post(const Message& message) {
  bool is_not_posting = outgoing.empty();

  if (is_not_posting) {
    outgoing.push(message);
    async_write_message();
  }
}

void chat::session::async_read_body() {
  io::async_read_until(connected_sock, body_buff, "\nEOF",
                       [self = shared_from_this()](
                           error_code error, std::size_t bytes_transferred) {
                         self->on_read_body(error, bytes_transferred);
                       });
}

void chat::session::on_read_body(error_code error,
                                 std::size_t bytes_transferred) {
  if (!error) {
    std::stringstream message;
    // TODO: ADD formating for name
    message << name << ": " << std::istream(&body_buff).rdbuf();

    body_buff.consume(bytes_transferred);

    // TODO: Inside the completion handeler (on_succefull_read) we want to
    // add the message to the chat room and deliver to all connected clients.
    on_susccesful_read(message.str());
    async_read_body();
  } else {
    if (io::error::not_found == error.value()) {
      // Body is to long.
    } else {
      connected_sock.close();
      on_error();
    }
  }
}

void chat::session::async_write_message() {
  // TODO: compose a more useful message
  // TODO: Make sure to format the name before sending.
  std::array<io::const_buffer, 3> view{io::buffer(outgoing.front().getName()),
                                       io::buffer(": "),
                                       io::buffer(outgoing.front().getBody())};

  io::async_write(connected_sock, view,
                  [self = shared_from_this()](error_code error,
                                              std::size_t bytes_transferred) {
                    self->on_write_message(error, bytes_transferred);
                  });
}

void chat::session::on_write_message(error_code error,
                                     std::size_t bytes_transferred) {
  if (!error) {
    outgoing.pop();

    if (!outgoing.empty()) {
      async_write_message();
    }
  } else {
    connected_sock.close(error);
    on_error();
  }
}
