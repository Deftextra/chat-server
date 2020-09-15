#include <iostream>
#include <server.hpp>

int main(int argc, char* argv[]) {
  io::io_context io_context;
  chat::server srv(io_context, 15001);
  srv.async_accept();
  io_context.run();
}