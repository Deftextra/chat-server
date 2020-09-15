#include "server.hpp"

#include <functional>

chat::server::server(io::io_context& io_context, std::uint16_t port)
    : acceptor{io_context, tcp::endpoint{tcp::v4(), port}},
      io_context{io_context} {}

void chat::server::async_accept() {
  acceptor.async_accept([this](error_code error, tcp::socket socket) {
    if (!error) {
      auto client = std::make_shared<session>(std::move(socket));

      chat_room.join(client);
      client->post(client->compose_name() + " has joined the chat");

      client->start(
          std::bind(&room::broadcast, &chat_room, std::placeholders::_1),
          [&, client] {
            chat_room.leave(client);
            // TODO: capture the case when session has no name. This should
            // never occur.
            chat_room.broadcast(client->compose_name() + " has left the chat");
          });

      async_accept();
    }
  });
}
