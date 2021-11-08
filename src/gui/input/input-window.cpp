#include "./input-window.hpp"

#include <stdio.h>

#include <iostream>

InputWindow::InputWindow(std::string title, int height, int width, int startHeight, int startWidth)
    : BoxWindow::BoxWindow(title, height, width, startHeight, startWidth) {
    std::thread drawer(&InputWindow::draw, this);
    drawer.detach();
    communicator = Communicator::getInstance();
    scrollok(window, true);
}

void InputWindow::draw() {
    setup();
    wrefresh(container);
    char string[communicator->maxMessageSize - 56];

    wgetnstr(window, string, communicator->maxMessageSize - 56);

    onInput(string);
    wclear(window);
    wrefresh(window);
    draw();
}

void InputWindow::onInput(std::string input) {
    if (input[0] == ':' && input[1] == 'q') {
        endwin();
        communicator->disconnect();
        exit(0);
    } else {
        communicator->sendMessage((input.c_str()));
    }
}