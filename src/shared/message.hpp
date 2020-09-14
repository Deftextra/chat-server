#ifndef MESSAGE_H
#define MESSAGE_H

#define MAX_NAME_SIZE 64
#define MAX_BODY_SIZE 512

#include <array>
namespace chat {
class Message {
 public:
  // Throw exception whenever we go above limit.
  Message(const std::string& name) : body{} {
    if (name.size() > MAX_NAME_SIZE) {
      throw "Name is to long";
    }
    this->name = name;
  }

  void setBody(const std::string& body) {
    if (body.size() > MAX_BODY_SIZE) {
      throw "Body size is to large";
    }

    this->body = body;
  }

  const std::string& getBody() { return body; }
  const std::string& getName() { return name; }

 private:
  std::string name;
  std::string body;
};

}  // namespace chat

#endif  // MESSAGE_H