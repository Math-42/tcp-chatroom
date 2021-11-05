#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define BUFFER_SIZE 255 //Tamanho das mensagens

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

    
    int sockfd, newSockFd, portNum, n;
    struct sockaddr_in serv_addr, cli_addr;
    char buffer[BUFFER_SIZE];
    socklen_t clilen;

    //Criar o socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
        error("ERRO: Criação do socket mal sucedida");
