#pragma once
#include <sstream>
#include <vector>

#include "../box-window/box-window.hpp"

class ChatWindow : public BoxWindow {
   private:

   public:
    /**
	 * Construtor da janela
	 * @param title titulo da janela
	 * @param height altura da janela
	 * @param width largura da janela
	 * @param startHeigh posição X onde a janela será desenhada
	 * @param startWidth posição Y onde a janela será desenhada
	 */
    ChatWindow(std::string title, int height, int width, int startHeight, int startWidth);
    /**
	 * Função que indica como a janela deve ser desenhada
	 */
    void draw();

};