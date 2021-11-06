/*
* To tentando aprender como que faz o esquema das janelas. Basicamente
*   o que tem implementado ate agora eh:
*
*   Tres Janelas:
*       - uma que mostra os usuarios online                 (funcionando mas pode melhorar)    
*       - uma para mostrar as mensagens                     (funcionando mas pode melhorar)
*       - uma para a pessoa digitar uma mensagem e enviar   (funcionando mas pode melhorar)
*
*   O codigo funciona assim:
*       a pessoa digita algo no terminal e quando aperta enter, a mensagem aparece na tela de chat
*       a caixa de escrita de mensagem eh apagada pra ela poder escrever outra mensagem 
*       pra sair tem que apertar o '~'
*       pra mensagem, o que eu to fazendo eh ler cada char e colocar ele no final de um std::string (nao sei se eh o
*    melhor metodo, ate pq a maioria das funcoes tem que colocar um *char, mas eu fiz uma gambiarra usando string.data() na verdade.
*    o unico beneficio eh nao ter que ficar criando aqueles vetor de char esquisito e com a std::string o tamanho fica certinho tbm)
*
*
*   Coisas que estou tentando descobir como fazer:
*       - (4/11/21) dar um jeito de colocar uma mensagem em baixo da outra na tela de mensagens sem
*       quebrar a borda da janela e quem sabe dar um scroll na pagina, pras mensagens irem subindo tlg (feito)
*       - (5/11/21) ver se tem algum jeito de o cara poder usar o backspace, e realmente apagar a mensagem enquanto ele ta escrevendo
*       quem sabe um buffer ou algo do tipo (feito)
*       
*
*   To-Do :
*       - deixar o codigo mais modularizado pra ficar mais facil de integrar com o resto do programa    (feito)
*       - fazer aparecer os nomes na tela de pessoas online                                             (feito)
*       - resolver o bug da primeira mensagem estar deslocada para a esquerda                           (feito)
*       - poder ver o historico de mensagens
*       - impedir que o usuario envie mensagens vazias                                                  (feito)
*
*   Incapacidades:
*       - se o cara errar a mensagem ele pode dar backspace, mas como to usando o echo do terminal, a letra errada nao apaga
*         ate que ele escreva algo por cima, mas a mensagem sai certa (concertado)
*       - se a mesnsagem for muito grande, ela vai inevitavelmente destruir a caixa onde manda as mensagens (concertado)
*       
*/


#include "gui.h"


int main(int argc, char *argv[]){

    WINDOW *w_online;
    PWIN    p_online;
    WINDOW *sw_online;

    WINDOW *w_chat;
    PWIN    p_chat;
    WINDOW *sw_chat;    //sub window no chat ---> preserva as bordas
    //PWIN    sp_chat;

    WINDOW *w_msg;
    PWIN    p_msg;
    WINDOW *sw_msg;     //sub window na msg ---> preserva as bordas
    //PWIN    sp_smg;

    int ch;

    string input;
    string username = "Mussattinho";
    vector<string> online;

//Setup
    setup();

//Verifica tamanho do terminal. Se for menor, as janelas ficam sobrepostas
    if ((LINES < 30) || (COLS < 90)) {
        endwin();
        puts("Seu terminal precisa ser pelo menos 90x30");
        exit(2);
    }

//Cores
    init_pair(1, COLOR_CYAN, COLOR_BLACK);


//Mensagens tela incial
    attron(COLOR_PAIR(1));
    printw("Pressione \'~\' para sair");
    printw("   Lines: %d, Columns %d", LINES, COLS);
    refresh();
    attroff(COLOR_PAIR(1));

//Cria Janelas
    w_online = create_newwin(&p_online, ONLINE);
    w_msg = create_newwin(&p_msg, MSG);
    w_chat = create_newwin(&p_chat, CHAT);

//Cria sub-janelas
    sw_chat = create_newsubwin(w_chat, &p_chat);
    sw_msg = create_newsubwin(w_msg, &p_msg);
    sw_online = create_newsubwin(w_online, &p_online);

//Adiciona usuarios online
    online.push_back(username);
    online.push_back("Anakolas");
    online.push_back("Mr. Dois");
    online.push_back("Scherlock");
    online.push_back("Jao");

    print_users(sw_online, online);

//Mensagens janela Online
    /* escreve_msg(sw_online, "Usuarios Conectados:\n\n");
    waddch(sw_online, ACS_DIAMOND);
    escreve_msg(sw_online, " "+username+"\n\n");
    escreve_msg(sw_online, "Mussattinho");
    wrefresh(w_online); */


//Leitura das mensagens
    keypad(sw_msg, TRUE);       // Leitura de teclas especiais na janela chat (F1, direcionais, ...) 

    nocbreak();                 // terminal controla o backspace
    echo();                     //letras dogitadas sao mostradas o terminal

    wmove(sw_msg, 0, 0);        //move cursor para onde comeca a caixa de escrita
    wrefresh(sw_msg);           //refresh na janela msg

    ch = '0';   //numero generico so pra comecar

//Loop principal do programa
    while (ch != '~')
    {
        /*reset na mensagem*/
        input.clear();

        while ( ch != '\n' ) //loop para leitura da mensagem
        {
            ch = wgetch(sw_msg);

            if (ch == '~') break;
            else if(ch == '\n' && input.empty()) //impede mensagens vazias
            {
                ch = '0';
                continue;   
            }

            input.push_back( ch );
        }

        if (ch != '~') 
        {
            ch = '0';   //reset pq se n, o ultimo char vai ser um '\n' --> nao vai ler outra mensagem
            input.insert(0,username+": ");
            escreve_msg(sw_chat, input);
        }  
        else
        {
            escreve_msg(sw_chat, "\t\t\t"+username+" saiu!");
        }
                
        wclear(sw_msg);             //limpa a caixa de mensagem
        wmove(sw_msg, 0, 0);        //move cursor para onde comeca a caixa de escrita
        wrefresh(sw_msg);           //refresh na janela msg
    }

    refresh();

    getch();            //por algum motivo, precisa dessas duas expressoes pro programa nao fechar 
    wgetch(sw_msg);     //automaticamente depois de um '~'

    /* destroi as janelas */
    wclear(w_online);
    wclear(w_msg);
    wclear(w_chat);

    destroy_win(sw_msg);
    destroy_win(sw_chat);
    destroy_win(w_online);
    destroy_win(w_chat);
    destroy_win(w_chat); 

    /* fecha o ncurses*/
    endwin();
    return 0;
}

