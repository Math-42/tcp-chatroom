#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define buffer 255 //Tamanho das mensagens

void error(const char *msg_error)
{
    perror(msg_error);
    exit(1);
}

int main(int argc, char *argv[])
{
    //Recebe o nome do arquivo e numero de PORT
    if(argc < 2)
        error("ERRO: Insira o nome do arquivo e o nro do PORT");

    
    int sockfd, newSockFd, portNum;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;

    //Criar o socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
        error("ERRO: Criação do socket mal sucedida");

    //Configurando o servidor
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portNum = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portNum); //Função htons garante que serv e cli se comuniquem em um mesmo "endian"
    
    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        error("Erro na configuração do servidor");
    }

    //Configuração inicial do servidor concluída

    return 0;
}
