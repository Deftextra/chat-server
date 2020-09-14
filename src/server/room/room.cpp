#include "room.hpp"

void chat::room::join(chat::participant_ptr participant) {
  participants.insert(participant);
  for (auto msg : recent_messages) participant->post(msg);
}

void chat::room::leave(participant_ptr participant) {
  participants.erase(participant);
}

void chat::room::broadcast(const Message& msg) {
  recent_messages.push_back(msg);
  while (recent_messages.size() > max_recent_msgs) recent_messages.pop_front();

  for (auto participant : participants) participant->post(msg);
}
