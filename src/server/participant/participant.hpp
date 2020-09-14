#ifndef PARTICIPANT_HPP
#define PARTICIPANT_HPP

#include <memory>

#include "message.hpp"

namespace chat {
class participant {
 public:
  virtual ~participant() {}
  virtual void post(const Message& msg) = 0;
};

typedef std::shared_ptr<participant> participant_ptr;

}  // namespace chat

#endif /* PARTICIPANT_HPP */
