#include "./chat-window.hpp"

ChatWindow::ChatWindow(std::string title, int height, int width, int startHeight, int startWidth)
    : BoxWindow::BoxWindow(title, height, width, startHeight, startWidth) {
    scrollok(window, true);  //adiciona um scroll na janela de mensagem
}

void ChatWindow::draw() {
    wclear(window);  //limpa a janela
    int y, x;
    curs_set(0);
    getyx(window, y, x);  //pega a posição atual do cursor
    for (auto message : GlobalControler::messageHistory) {
        waddstr(window, ((message + "\n").c_str()));  //adiciona cada mensagem na tela do chat
    }
    wmove(window, y, x);  //volta para a posição inicial
    curs_set(0);
}
