#include "session.hpp"

chat::session::session(tcp::socket&& socket)
    : connected_sock{std::move(socket)}, body_buff(MAX_BODY_SIZE) {}

void chat::session::start(message_handler&& on_message,
                          error_handler&& on_error) {
  this->on_successful_read = std::move(on_message);
  this->on_error = std::move(on_error);

  query_for_name();
}

void chat::session::query_for_name() {
  io::async_write(connected_sock, io::buffer("Enter name: "),
                  [self = shared_from_this()](error_code error,
                                              std::size_t bytes_transferred) {
                    self->on_query_for_name(error, bytes_transferred);
                  });
}

void chat::session::on_query_for_name(error_code error,
                                    std::size_t bytes_transferred) {
  if (!error) {
    get_name();
  } else {
    connected_sock.close();
    on_error();
  }
}

void chat::session::get_name() {
  io::async_read_until(connected_sock,
                       io::dynamic_buffer(name_buff, MAX_NAME_SIZE), '\n',
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
    // Write method that will  compose message.
    Message msg{this->compose_body()};
    msg.setName(this->compose_name());

    body_buff.consume(bytes_transferred);
    on_successful_read(msg);
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
  // Compose message buffer view.
  auto message = outgoing.front();

  std::vector<io::const_buffer> view;

  //TODO: composing the message should be handeled by the client. We should minimise.
  // the amount of data being transferred.
  view.push_back(io::buffer("\n--------------------\n"));

  if (message.getName().empty()) {
    view.push_back(io::buffer(outgoing.front().getBody()));
  } else {
    view.push_back(io::buffer(outgoing.front().getName()));
    view.push_back(io::buffer(" says:\n"));
    view.push_back(io::buffer(outgoing.front().getBody()));
  }

  // Write message buffer view
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

std::string chat::session::compose_name() {
  std::string name;
  std::istringstream sname{name_buff};
  std::getline(sname, name);

  return name;
}
std::string chat::session::compose_body() {
  std::string body;
  std::string line;

  std::istream ibody{&body_buff};

  while (std::getline(ibody, line) && line != "EOF") {
    body += (line + "\n");
  }

  return body;
}
