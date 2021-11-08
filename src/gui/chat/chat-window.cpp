#include "./chat-window.hpp"

ChatWindow::ChatWindow(std::string title, int height, int width, int startHeight, int startWidth)
    : BoxWindow::BoxWindow(title, height, width, startHeight, startWidth) {
    scrollok(window, true);
}

void ChatWindow::draw() {
    wclear(window);
    int y, x;
    curs_set(0);
    getyx(window, y, x);
    for (auto message : GlobalControler::messageHistory) {
        waddstr(window, ((message + "\n\n").c_str()));
    }
    wmove(window, y, x);
    curs_set(0);
}

void ChatWindow::setMessageHistory(std::vector<std::string>* newMessageHistory) {
    messageHistory = newMessageHistory;
    refresh();
}