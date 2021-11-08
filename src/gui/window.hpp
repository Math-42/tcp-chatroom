#pragma once
#include <ncurses.h>

#include <chrono>
#include <thread>

#include "./chat/chat-window.hpp"
#include "./input/input-window.hpp"

class Window {
   private:
    WINDOW* mainWindow;
    ChatWindow* chat;
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