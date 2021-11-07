#include "./box-window.hpp"

#include <iostream>
BoxWindow::BoxWindow(int height, int width, int startHeight, int startWidth) : title{""} {
    container= newwin(height, width, startHeight, startWidth);
    window = newwin(height-2, width-2, startHeight+1, startWidth+1);
    setup();
}

BoxWindow::BoxWindow(std::string title, int height, int width, int startHeight, int startWidth) : title{title} {
    container= newwin(height, width, startHeight, startWidth);
    window = newwin(height-2, width-2, startHeight+1, startWidth+1);
    setup();
}

BoxWindow::~BoxWindow() {
    delwin(window);
}

void BoxWindow::refresh() {
    setup();
    wrefresh(container);
    draw();
    wrefresh(window);
}

void BoxWindow::setup() {
    box(container, ACS_VLINE, ACS_HLINE);
    if (title != "") mvwprintw(container, 0, 2, ("|" + title + "|").c_str());
}
