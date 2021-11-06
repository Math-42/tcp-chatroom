#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

#define BUFFER_SIZE 255 //Tamanho das mensagens

void error(const char *msg_error)
{
    perror(msg_error);
    exit(1);
}

void *thread_le(void *arg);
void *thread_escreve(void *arg);

int main(int argc, char *argv[])
{
    //Recebe o nome do arquivo e numero de PORT
    if(argc < 3)
        error("ERRO: Insira o nome do arquivo, IP e o nro do PORT");

    //Variaveis iniciais
    int sockfd, portNum, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[BUFFER_SIZE];

    //Criar socket
    portNum = atoi(argv[2]);
    sockfd = socket (AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
        error("Erro na criacao do socket");
    
    //Configuracao da conexao com servidor
    server = gethostbyname(argv[1]);
    if(server == NULL)
        error("ERRO na conexao com servidor");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portNum);


        //Tenta conectar
        if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
            error("Erro na conexão");
        
        //Faz o que o programa deve fazer  no servidor
        pthread_t c, t;
        int *pclient = (int *) malloc(sizeof(int));
        *pclient = sockfd;
        pthread_create(&t, NULL, thread_le, pclient);
        pthread_create(&c, NULL, thread_escreve, pclient);

    //close(sockfd);
    while(1){}
    return 0;
}

void *thread_le(void *arg)
{
    int sockfd =  *((int*) arg);
    free(arg); //Nao precisamos mais deste ponteiro

    char buffer[BUFFER_SIZE];

    while(1)
    {
        bzero(buffer, BUFFER_SIZE);
        fgets(buffer, BUFFER_SIZE, stdin);
        for(int k = 0; k < BUFFER_SIZE; k++)
        {
            if(buffer[k] == '\n')
            {
                buffer[k] = '\0';
                break;
            }
        }
    
        if(write(sockfd, buffer, strlen(buffer)) < 0)
            error("Erro ao enviar mensagem");
    }

    return NULL;
}

void *thread_escreve(void *arg)
{   
    int sockfd =  *((int*) arg);
    free(arg); //Nao precisamos mais deste ponteiro

    char buffer[BUFFER_SIZE];
    while(1){
        
        int rec = read(sockfd, buffer, BUFFER_SIZE);
        if( rec < 0)
            error("Erro ao receber msg do servidor");
        else if(rec > 0)
        {
            printf("%s\n", buffer);
            fflush(stdout);
            bzero(buffer, BUFFER_SIZE);
        }
    }
    
    return NULL;
}

