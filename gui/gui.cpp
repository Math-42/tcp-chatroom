/*
* To tentando aprender como que faz o esquema das janelas. Basicamente
*   o que tem implementado ate agora eh:
*
*   Tres Janelas:
*       - uma que mostra os usuarios online (nao implementado)    
*       - uma para mostrar as mensagens (em progresso)
*       - uma para a pessoa digitar uma mensagem e enviar (mais ou menos implementada)
*
*   O codigo funciona assim:
*       a pessoa digita algo no terminal e quando aperta enter, a mensagem aparece na tela de chat
*       a caixa de escrita de mensagem eh apagada pra ela poder escrever outra mensagem 
*       pra sair tem que apertar o F1
*       pra mensagem, o que eu to fazendo eh ler cada char e colocar ele no final de um std::string (nao sei se eh o
*    melhor metodo, ate pq a maioria das funcoes tem que colocar um *char, mas eu fiz uma gambiarra usando string.data() na verdade.
*    o unico beneficio eh nao ter que ficar criando aqueles vetor de char esquisito e com a std::string o tamanho fica certinho tbm)
*
*
*   Coisas que estou tentando descobir como fazer:
*       - dar um jeito de colocar uma mensagem em baixo da outra na tela de mensagens sem
*       quebrar a borda da janela e quem sabe dar um scroll na pagina, pras mensagens irem subindo tlg  
*       
*
*   To-Do :
*       - deixar o codigo mais modularizado pra ficar mais facil de integrar com o resto do programa
*       - fazer aparecer os nomes na tela de pessoas online
*
*
*   Incapacidades:
*       - se o cara errar a mensagem ele pode dar backspace, mas como to usando o echo do terminal, a letra errada nao apaga
*         ate que ele escreva algo por cima, mas a mensagem sai certa
*       - se a mesnsagem for muito grande, ela vai inevitavelmente destruir a caixa onde manda as mensagens
*       
*/


#include <ncurses.h>
#include <string>

using namespace std;

//guarda os parametros da janela
typedef struct _WIN_struct { 
  int startx, starty;
  int height, width;
}PWIN;

//tipos de window
enum {ONLINE, CHAT, MSG};

//funções 
void escreve_msg (WINDOW *local_win, string msg);
WINDOW *create_newwin(PWIN *p_win, int type);
void destroy_win(WINDOW *local_win);


int main(int argc, char *argv[]){

    WINDOW *w_online;
    PWIN    p_online;

    WINDOW *w_chat;
    PWIN    p_chat;
    WINDOW *sw_chat;    //sub window no chat ---> preserva as bordas
    PWIN    sp_chat;

    WINDOW *w_msg;
    PWIN    p_msg;
    WINDOW *sw_msg;
    PWIN    sp_smg;

    int ch;

    std::string input;

//Setup
    initscr();              /*Incia o ncurses*/
    start_color();          /* Começa a funcionalidade das cores */
    raw();
    //cbreak();             /* Buffer de linha desativado*/
    keypad(stdscr, TRUE);	/* Leitura de teclas especiais no stdscr (F1, direcionais, ...) */
    //noecho();               
    //curs_set( false );

//Verifica tamanho do terminal. Se for menor, as janelas ficam sobrepostas
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
    w_msg = create_newwin(&p_msg, MSG);
    w_chat = create_newwin(&p_chat, CHAT);

//Cria sub-janelas
    sw_chat = derwin(w_chat, p_chat.height-2, p_chat.width-2, 1, 1);
    if (sw_chat == NULL)
    {
        waddstr(w_chat, "Deu ruim na subwindow!");
        endwin();
        return 1;
    }
    
    // wbkgd(sw_chat, COLOR_PAIR(1));  //DEBUG --- Pinta o background da subjaneal
    wrefresh(sw_chat);
    scrollok(sw_chat,TRUE);  //habilita o scroll na janela de chat

    sw_msg = derwin(w_msg, p_msg.height-2, p_msg.width-2, 1, 1);
    if (sw_msg == NULL)
    {
        waddstr(w_msg, "Deu ruim na subwindow!");
        endwin();
        return 1;
    }
    wrefresh(sw_chat);
    scrollok(sw_msg, TRUE);

//Mensagens janela Online
    mvwprintw(w_online, 1, 1, "Usuarios Conectados:");  
    wrefresh(w_online);

    // wmove(sw_chat, 0, 0);        //move cursor para a janela de chat


    keypad(sw_msg, TRUE);        // Leitura de teclas especiais na janela chat (F1, direcionais, ...) 
    echo();                     //letras dogitadas sao mostradas o terminal
    wmove(sw_msg, 0, 0);         //move cursor para onde comeca a caixa de escrita
    wrefresh(sw_msg);            //refresh na janela msg

    ch = wgetch(sw_msg);         //le o char da janela de msg
    while (ch != KEY_F(1))
    {
        while (ch != '\n') 
        {
            if (ch == KEY_F(1)) {break;}  

            else if (ch == KEY_BACKSPACE) { input.erase(input.size()-1); }     //esse if eh pra funcionar o backspace

            else if (ch == KEY_UP) {wscrl(w_chat, -1);}     // isso nao ta funcionando ainda, to testando

            else{ input.push_back( ch ); }
             
            ch = wgetch(sw_msg);
        }
    
        
        escreve_msg(sw_chat, input);
        
        /* reset na mensagem e no char atual*/
        input.clear();
        if(ch != KEY_F(1)){ch = ' ';}  //reset ch

        //limpa a caixa de mensagem
        wclear(sw_msg);
        //wborder(w_msg, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
        wmove(sw_msg, 0, 0);         //move cursor para onde comeca a caixa de escrita
        wrefresh(sw_msg);            //refresh na janela msg
    }

    

    refresh();
    getch();

    /* destroi as janelas */
    wclear(w_online);
    wclear(w_msg);
    destroy_win(w_online);
    destroy_win(w_chat);

    /* fecha o ncurses*/
    endwin();
    return 0;
}


// funcao para escrever uma mensagem em uma janela
void escreve_msg (WINDOW *local_win, string msg)
{
    int y, x;       //coordenadas do cursor atual
    int row, col;   //tamanho da janela

    getyx(local_win, y, x);
    getmaxyx(local_win, row, col);

    if (y == row - 1) //esta na ultima linha
    {
        wscrl(local_win, 1);
        mvwaddstr(local_win, y, 1, msg.data());
    }
    else    //esta no meio da tela
    {
        mvwaddstr(local_win, y+1, 1, msg.data());
    }
    
    wrefresh(local_win);
}


// funcao para criar as janelas dependendo do tipo especificado
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


// funcao para destruir a janela, tem que retirar a borda primeiro, sla pq
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


