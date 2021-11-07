#pragma once
#include "../box-window/box-window.hpp"

class ChatTreeWindow : public BoxWindow {
   public:
    ChatTreeWindow(std::string title, int height, int width, int startHeight, int startWidth);
    void draw();
};