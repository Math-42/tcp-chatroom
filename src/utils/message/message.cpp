#include "message.hpp"

Message::Message(std::string sender, std::string content)
    : sender{sender},
      content{content} {
    std::time_t now = time(0);
    data = std::ctime(&now);
    data.pop_back();
}

Message::Message(std::string sender, std::string data, std::string content)
    : sender{sender},
      content{content},
      data{data} {
}

void Message::serialize() {

}