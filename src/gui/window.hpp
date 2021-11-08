#pragma once
#include <ncurses.h>

#include <chrono>
#include <thread>

#include "./chat/chat-window.hpp"
#include "./input/input-window.hpp"

class Window {
   private:
    WINDOW* mainWindow;
    ChatWindow* chat;
    InputWindow* input;

    int maxRows;
    int refreshRate;
    int delaySize;
    int maxColumns;

   public:
    /**
	* Construtor da janela do programa
	* @param refreshRate indica quantas vezes por segundo a janela deve ser desenhada
	*/
    Window(int refreshRate);
    /**
	 * Destrutor da janela
	 */
    ~Window();

    /**
	 * Inicializa a janela com o seu setup e começa a desenhar
	 */
    void show();

   private:
    /**
	* Realiza uma refresh das janelas e de sua suas sub janelas
	*/
    void refresh();
};