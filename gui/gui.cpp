#include <ncurses.h>
#include <string>

using namespace std;

//guarda os parametros da janela
typedef struct _WIN_struct { 
  int startx, starty;
  int height, width;
}PWIN;

enum {ONLINE, CHAT, MSG};

WINDOW *create_newwin(PWIN *p_win, int type);
void destroy_win(WINDOW *local_win);


int main(int argc, char *argv[]){

    WINDOW *w_online;
    PWIN    p_online;

    WINDOW *w_chat;
    PWIN    p_chat;

    WINDOW *w_msg;
    PWIN    p_msg;

    int ch;
    std::string input;

//Setup
    initscr();              /*Incia o ncurses*/
    start_color();          /* Começa a funcionalidade das cores */
    raw();
    //cbreak();               /* Buffer de linha desativado*/
    keypad(stdscr, TRUE);	/* Leitura de teclas especiais no stdscr (F1, direcionais, ...) */
    //noecho();               
    //curs_set( false );

//Verifica tamanho
    if ((LINES < 30) || (COLS < 90)) {
        endwin();
        puts("Seu terminal precisa ser pelo menos 90x30");
        exit(2);
    }

//Cores
    init_pair(1, COLOR_CYAN, COLOR_RED);


//Mensagens tela incial
    attron(COLOR_PAIR(1));
    printw("Pressione F1 para sair");
    printw("   Lines: %d, Columns %d", LINES, COLS);
    refresh();
    attroff(COLOR_PAIR(1));

//Cria Janelas
    w_online = create_newwin(&p_online, ONLINE);
    w_chat = create_newwin(&p_chat, CHAT);
    w_msg = create_newwin(&p_msg, MSG);

//Mensagens janela Online
    mvwprintw(w_online, 1, 1, "Usuarios Conectados:");  
    wrefresh(w_online);
    wmove(w_chat, 1, 1);


    keypad(w_msg, TRUE);        // Leitura de teclas especiais na janela chat (F1, direcionais, ...) 
    echo();                     //letras dogitadas sao mostradas o terminal
    wmove(w_msg, 1, 2);         //move cursor para onde comeca a caixa de escrita
    wrefresh(w_msg);            //refresh na janela msg

    ch = wgetch(w_msg);
    while (ch != KEY_F(1))
    {
        while (ch != '\n')
        {
            if (ch == KEY_F(1)) {break;}  

            else if (ch == KEY_BACKSPACE) { input.erase(input.size()-1); }

            else if (ch == KEY_UP) {wscrl(w_chat, -1);}

            else{ input.push_back( ch ); }
             
            ch = wgetch(w_msg);
        }
    
        //wclear(w_chat);
        //wborder(w_chat, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
        wscrl(w_chat, 1);
        input.push_back('\n');
        waddstr(w_chat, input.data());
        wrefresh(w_chat);

        //mvwaddstr(w_chat, 3 ,3, "teste");
        //wrefresh(w_chat);

        input.clear();
        if(ch != KEY_F(1)){ch = ' ';}  //reset ch

        wclear(w_msg);
        wborder(w_msg, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
        wmove(w_msg, 1, 2);         //move cursor para onde comeca a caixa de escrita
        wrefresh(w_msg);            //refresh na janela msg
    }

    
    

    

    refresh();
    getch();

    wclear(w_online);
    destroy_win(w_online);

    //getch();
    destroy_win(w_chat);
    endwin();
    return 0;
}

WINDOW *create_newwin(PWIN *p_win, int type)
{
    
    switch (type)
    {
    case ONLINE:     //janela de pessoas online
        p_win->height = LINES - 2;
        p_win->width = COLS*1/4 ;

        p_win->starty = 1;     
        p_win->startx = 1;   
        break;

    case CHAT:
        p_win->height = LINES*4/5;
        p_win->width = COLS*3/4 - 6 ;

        p_win->starty = 1;     
        p_win->startx = COLS/4 + 3;   
        break;
    
    case MSG:
        p_win->height = LINES/5 - 2;
        p_win->width = COLS*3/4 - 6 ;

        p_win->starty = LINES*4/5 + 2;     
        p_win->startx = COLS/4 + 3;    
        break;

    default:
        p_win->height = 10;
        p_win->width = 10;
        p_win->starty = 2;
        p_win->startx = 2;
        break;

    }

    WINDOW *local_win;

    local_win = newwin(p_win->height, p_win->width, p_win->starty, p_win->startx);

    wborder(local_win, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

    wrefresh(local_win); /* Mostra aquela caixa 	*/

    return local_win;
}


void destroy_win(WINDOW *local_win){	

      wborder (local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  /* Os parâmetros usados são
    * 1. win: a janela na qual operar
    * 2. ls: caractere a ser usado para o lado esquerdo da janela
    * 3. rs: caractere a ser usado para o lado direito da janela
    * 4. ts: caractere a ser usado na parte superior da janela
    * 5. bs: caractere a ser usado na parte inferior da janela
    * 6. tl: caractere a ser usado para o canto superior esquerdo da janela
    * 7. tr: caractere a ser usado no canto superior direito da janela
    * 8. bl: caractere a ser usado no canto inferior esquerdo da janela
    * 9. br: caractere a ser usado no canto inferior direito da janela
    */
    wrefresh(local_win);
    delwin(local_win);
}


