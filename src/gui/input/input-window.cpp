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
    char buffChar = ' ';
    std::string strInput;

    while (true) {
        buffChar = wgetch(window);
        if (buffChar == '\n') break;
        strInput += buffChar;
    };

    onInput(strInput);
    wclear(window);
    wrefresh(window);
    draw();
}

void InputWindow::onInput(std::string input) {
    std::cout << input << std::endl;
    printf("%s", input.c_str());
    communicator->sendMessage((input.c_str()));
    if (input == ":q\0") {
        endwin();
        exit(0);
    }
}
