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
    if(argc < 3)
        error("ERRO: Insira o nome do arquivo, IP e o nro do PORT");

    
    int sockfd, portNum, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[BUFFER_SIZE];

    portNum = atoi(argv[2]);

    return 0;
}
