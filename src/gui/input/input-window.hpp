#pragma once
#include "../../communicator/communicator.hpp"
#include "../box-window/box-window.hpp"
#include <csignal>
class InputWindow : public BoxWindow {
   private:
    Communicator* communicator;

   public:
    InputWindow(std::string title, int height, int width, int startHeight, int startWidth);
    void draw();
    void onInput(std::string input);
};