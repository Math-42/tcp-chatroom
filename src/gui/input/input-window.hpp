#pragma once
#include <csignal>

#include "../../communicator/communicator.hpp"
#include "../box-window/box-window.hpp"
class InputWindow : public BoxWindow {
   private:
    Communicator* communicator;

   public:
    /**
	 * Construtor da janela
	 * @param title titulo da janela
	 * @param height altura da janela
	 * @param width largura da janela
	 * @param startHeigh posição X onde a janela será desenhada
	 * @param startWidth posição Y onde a janela será desenhada
	 */
    InputWindow(std::string title, int height, int width, int startHeight, int startWidth);
    /**
	 * Função que indica como a janela deve ser desenhada
	 */
    void draw();
    /**
	 * Função executada toda vez que um input é inserido 
	 */
    void onInput(std::string input);
};