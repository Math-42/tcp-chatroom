#include "./input-window.hpp"

#include <stdio.h>

#include <iostream>

InputWindow::InputWindow(std::string title, int height, int width, int startHeight, int startWidth)
    : BoxWindow::BoxWindow(title, height, width, startHeight, startWidth) {
    std::thread drawer(&InputWindow::draw, this);  //thread para ficar lendo a entrada do usuário
    drawer.detach();
    communicator = Communicator::getInstance();
    scrollok(window, true);  //adiciona scroll na tela
}

void InputWindow::draw() {
    setup();
    wrefresh(container);
    char string[communicator->maxMessageSize - 56];
    std::memset(string, 0, communicator->maxMessageSize - 56);
    //pega a string inserida pelo usuário
    wgetnstr(window, string, communicator->maxMessageSize - 56);

    onInput(string);
    wclear(window);
    wrefresh(window);
    draw();
}

void InputWindow::onInput(std::string input) {
    if (input[0] == ':' && input[1] == 'q') {
        raise(SIGTERM);  // finaliza o programa
    } else {
        communicator->sendMessage((input.c_str()));  // enviada a entrada lida
    }
}
