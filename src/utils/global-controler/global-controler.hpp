#pragma once
#include <string>
#include <vector>

#include "../message/message.hpp"

class GlobalControler {
   public:
    static std::vector<std::string> messageHistory;

   public:
    static void addNewMessage(std::string newMessage);
};