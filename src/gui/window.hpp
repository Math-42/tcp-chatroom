#pragma once
#include <ncurses.h>

#include <chrono>
#include <thread>

#include "./chat-tree/chat-tree-window.hpp"
#include "./chat/chat-window.hpp"
#include "./input/input-window.hpp"
#include "./users/user-window.hpp"

class Window {
   private:
    WINDOW* mainWindow;
    UserWindow* users;
    ChatWindow* chat;
    ChatTreeWindow* chatTree;
    InputWindow* input;

    int maxRows;
    int refreshRate;
    int delaySize;
    int maxColumns;

   public:
    Window(int height, int width, int refreshRate);
    ~Window();
    void show();

   private:
    void refresh();
};