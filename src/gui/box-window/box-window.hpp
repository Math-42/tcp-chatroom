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
    /**
	 * Faz o setup inicial da janela criando a caixa de caracteres com o título
	 */
    void setup();

   public:
    /**
	 * Construtor da janela
	 * @param title titulo da janela
	 * @param height altura da janela
	 * @param width largura da janela
	 * @param startHeigh posição X onde a janela será desenhada
	 * @param startWidth posição Y onde a janela será desenhada
	 */
    BoxWindow(std::string title, int height, int width, int startHeight, int startWidth);

    /**
	 * Destrutor da janela
	 */
    ~BoxWindow();

    /**
	 * Função virtual que deve ser sobrescrita para indicar como a janela deve ser desenhada
	 */
    virtual void draw() = 0;

    /**
	 * Faz o refresh da janela atualizando de acordo com o que está escrito no buffer
	 */
    void refresh();
};