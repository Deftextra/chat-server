# Simple chat application example.

![workflow](https://github.com/Deftextra/chat-server/workflows/chat-server%20build/badge.svg)
![license](https://camo.githubusercontent.com/bef6126309622c5d9e6e82cfe41b88a78a8ccf71/68747470733a2f2f696d672e736869656c64732e696f2f6769746875622f6c6963656e73652f686f73706974616c72756e2f686f73706974616c72756e)


## Motivation
This code is not meant to be used in a production environment and is mainly written
for personal educational purposes. As such, the build pipe-line and dev environment
is likely an overkill for the size of the current project, but can serve as a starting template for larger projects with similar aim.

## Server
### Functionality
* Each server should have an instance of a chat room
* The chat room should contain all to current active participants, which are a type of active sessions.
* The server should promt and store the name of each participant when creating a new session.
* When broadcasting a chat messages, the name of the owner of the message should be printed first.

Quick overview of current build status:

```mermaid
classDiagram
    messageQueue o-- message
    session <-- participants
    server *-- room
    messageQueue --o room
    room o-- participants
    message o-- participants

      class server{
          -io_context io
          -acceptor acceptor
          -async_accept()
          +start()
  
      }
      class session{
          -socket connected_sock
          -queue<string>
          -streambuffer sbuff
          -function messsage_handler
          -function error_handler
          -async_write()
          -async_read()
          +put()
          +start()
          
      }
      class messageQueue{
          +push
          +pop
          
      }
      class message{
          -string name
          -string body
          +set_name()
          +get_name()
          
      }
      class participants{
          -string name;
          
      }
      class room{
          +join()
          +leave()
          +broadcast()
          
      }

