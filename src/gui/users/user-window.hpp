#pragma once
#include "../box-window/box-window.hpp"
#include "../chat/chat-window.hpp"
#include "../chat-tree/chat-tree-window.hpp"
#include "../input/input-window.hpp"

class UserWindow : public BoxWindow {
   public:
    UserWindow(std::string title, int height, int width, int startHeight, int startWidth);
    void draw();
};