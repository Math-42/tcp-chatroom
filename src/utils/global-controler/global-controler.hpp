#pragma once
#include <string>
#include <vector>
#include "../message/message.hpp"

#define PORT 3030
#define MAX_MESSAGE_SIZE 80
#define ADDRESS "127.0.0.1"

class GlobalControler {
   public:
    static std::vector<Message> messageHistory;
    static std::vector<std::string> currUsers;
    static std::vector<std::string> allChats;

   public:
    static void addNewMessage(Message newMessage);
    static void updateCurrUsers(std::vector<std::string> newCurrUsers);
};