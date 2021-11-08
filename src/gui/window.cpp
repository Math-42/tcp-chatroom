#include "./window.hpp"

Window::Window(int minHeight, int minWidth, int refreshRate)
    : refreshRate{refreshRate} {
    initscr();
    start_color();
    keypad(stdscr, true);
    nocbreak();

    delaySize = 1000 / refreshRate;  // 1s/fps

    getmaxyx(stdscr, maxColumns, maxRows);
    maxColumns -= 2;
    maxRows -= 1;

    chat = new ChatWindow("Chat", (7 * maxColumns) / 8, 3 * maxRows / 4, 1, (maxRows / 8) + 1);
    input = new InputWindow("Message", maxColumns / 8 + 1, 3 * maxRows / 4, (7 * maxColumns / 8) + 1, (maxRows / 8) + 1);

    ::refresh();
}

Window::~Window() {
    endwin();
}

void Window::show() {
    std::thread drawer(&Window::refresh, this);
    drawer.detach();
}

void Window::refresh() {
    while (true) {
        chat->refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(delaySize));
    }
}