#ifndef ASP_HPP
#define ASP_HPP

#include <asio.hpp>
#include "message.hpp"

namespace io = asio;
using tcp = io::ip::tcp;
using error_code = asio::error_code;

using message_handler = std::function<void(chat::Message)>;
using error_handler = std::function<void()>;

#endif /* ASP_HPP */