#pragma once
#include <ncurses.h>

#include <string>
#include <thread>

#include "../../utils/global-controler/global-controler.hpp"

class BoxWindow {
   public:
    std::string title;
    WINDOW* container;
    WINDOW* window;

   protected:
    void setup();

   public:
    BoxWindow(int height, int width, int startHeight, int startWidth);
    BoxWindow(std::string title, int height, int width, int startHeight, int startWidth);
    ~BoxWindow();
    virtual void draw() = 0;
    void refresh();
};