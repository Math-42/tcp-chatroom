#pragma once
#include <sstream>
#include <vector>

#include "../box-window/box-window.hpp"

class ChatWindow : public BoxWindow {
   private:
    std::vector<std::string>* messageHistory = nullptr;

   public:
    ChatWindow(std::string title, int height, int width, int startHeight, int startWidth);
    void draw();
    void setMessageHistory(std::vector<std::string>* newMessageHistory);
};