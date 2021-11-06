#pragma once


#include <ncurses.h>
#include <vector>
#include <string>

using namespace std;

//guarda os parametros da janela
typedef struct _WIN_struct { 
  int startx, starty;
  int height, width;
}PWIN;

//tipos de window
enum {ONLINE, CHAT, MSG};

// Escreve uma mensagem em uma janela
void escreve_msg (WINDOW *local_win, string msg);

// Carrega as janelas do Ncurses
void setup ();

// funcao para criar as janelas dependendo do tipo especificado
WINDOW *create_newwin(PWIN *p_win, int type);

//Cria uma subjanela de uma janela pai
WINDOW *create_newsubwin(WINDOW *w_parent, PWIN *p_parent);

// Destroi a janela
void destroy_win(WINDOW *local_win);

//Printa usuarios online
void print_users (WINDOW *win, vector<string> users);