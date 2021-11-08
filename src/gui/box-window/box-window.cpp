#include "./box-window.hpp"

#include <iostream>

BoxWindow::BoxWindow(std::string title, int height, int width, int startHeight, int startWidth) : title{title} {
    container = newwin(height, width, startHeight, startWidth);               //cria um container que possui a caixa
    window = newwin(height - 2, width - 2, startHeight + 1, startWidth + 1);  //cria a janela real
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
    box(container, ACS_VLINE, ACS_HLINE);  //desenha a caixa em volta da janela criada
    if (title != "") mvwprintw(container, 0, 2, ("|" + title + "|").c_str());
}
