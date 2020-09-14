#ifndef ROOM_HPP
#define ROOM_HPP

#include <deque>
#include <set>

#include "../participant/participant.hpp"
#include "asp.hpp"

namespace chat {
class room {
 public:
  void join(participant_ptr participant);
  void leave(participant_ptr participant);
  void broadcast(const Message& msg);

 private:
  std::set<participant_ptr> participants;
  enum { max_recent_msgs = 100 };
  std::deque<Message> recent_messages;
};

}  // namespace chat

#endif /* ROOM_HPP */