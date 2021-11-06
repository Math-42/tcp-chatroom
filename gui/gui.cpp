#include "gui.h"




void escreve_msg (WINDOW *local_win, string msg)
{

    waddstr(local_win, msg.data());
    
    wrefresh(local_win);
}

void setup ()
{
    initscr();              /*Incia o ncurses*/
    start_color();          /* Começa a funcionalidade das cores */
    //raw();
    cbreak();             /* Buffer de linha desativado*/
    keypad(stdscr, TRUE);	/* Leitura de teclas especiais no stdscr (F1, direcionais, ...) */
    //noecho();               
    //curs_set( false );
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

    case CHAT:      //janela onde mostra o chat
        p_win->height = LINES*4/5;
        p_win->width = COLS*3/4 - 6 ;

        p_win->starty = 1;     
        p_win->startx = COLS/4 + 3;   
        break;
    
    case MSG:       //janela onde a pessoa escreve as mensagens
        p_win->height = LINES/5 - 2;
        p_win->width = COLS*3/4 - 6 ;

        p_win->starty = LINES*4/5 + 2;     
        p_win->startx = COLS/4 + 3;    
        break;

    default:        //teoricamente nunca vai ser usado
        p_win->height = 10;
        p_win->width = 10;
        p_win->starty = 2;
        p_win->startx = 2;
        break;

    }

    WINDOW *local_win;

    local_win = newwin(p_win->height, p_win->width, p_win->starty, p_win->startx);

    box(local_win,ACS_VLINE, ACS_HLINE);
    //wborder(local_win, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

    wrefresh(local_win); 

    return local_win;
}


WINDOW *create_newsubwin(WINDOW *w_parent, PWIN *p_parent)
{
    WINDOW *local_swin;

    local_swin = derwin(w_parent, p_parent->height-2, p_parent->width-2, 1, 1);
    if (local_swin == NULL)
    {
        waddstr(w_parent, "Deu ruim na subwindow!");    
        endwin();
        return NULL;
    }
    
    /* DEBUG --- Pinta o background da subjaneal
        init_pair(1, COLOR_CYAN, COLOR_RED);
        wbkgd(local_swin, COLOR_PAIR(1));  
    */

    scrollok(local_swin,TRUE);  //habilita o scroll na janela de chat
    wrefresh(local_swin);

    return local_swin;
}

/* 
    A maior parte dessa funcao ta comentada basicamente pq se vc quiser destruir uma janela e continuar rodando
    o programa, vc precisa "destruir" as bordas antes de destruir a janela

    Mas como por enquanto eu to fechando o programa junto com a destruicao das janelas, tanto faz

    Alem disso, tava dando uns problema de segfault que eu ainda nao cosnegui entender/resolver


 */
void destroy_win(WINDOW *local_win){	

    //tem que destruir a borda primeiro, substituindo por espacos
    //wborder (local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
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

    //wrefresh(local_win);
    delwin(local_win);
}


void print_users (WINDOW *win, vector<string> users)
{
    escreve_msg(win, "Usuarios Conectados:\n\n");

    for (int i = 0; i < users.size(); i++)
    {
        waddch(win, ACS_DIAMOND);
        escreve_msg(win, " "+users[i]+"\n\n");
        
    }
    wrefresh(win);
}