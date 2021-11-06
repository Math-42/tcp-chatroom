#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define BUFFER_SIZE 255 //Tamanho das mensagens
#define num_clientes 5
int vetor_clientes[num_clientes], i = 0;
pthread_mutex_t lock;

void error(const char *msg_error)
{
    perror(msg_error);
    exit(1);
}

void *thread_servidor(void *arg);

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

    //Preparar o servidor para "ouvir"
    listen(sockfd, num_clientes); //Numero limite de clientes
    clilen = sizeof(cli_addr);

    //Agora o programa entra em loop, e faz o que deve ser feito
    while(1)
    {
        //Aceitar a conexão
        newSockFd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if(newSockFd < 0)
            error("Erro ao aceitar clizente");

        pthread_t t;
        int *pclient = (int *) malloc(2*sizeof(int));
        pclient[0] = newSockFd;
        vetor_clientes[i] = newSockFd;
        pclient[1] = i;
        pthread_create(&t, NULL, thread_servidor, pclient);
        i++;
    }

    close(newSockFd);
    close(sockfd);
    return 0;
}

void *thread_servidor(void *arg)
{
    int client_socket =  *((int*) arg);
    int sock_aux;
    int i_aqui = *((int *) arg + 1);
    free(arg); //Nao precisamos mais deste ponteiro

    char buffer[BUFFER_SIZE];
    int j;

    printf("Aqui rodou a %d", i_aqui);
    fflush(stdout);

    while(1)
    {

        //Lê o que o cliente escreveu
        bzero(buffer, BUFFER_SIZE);
        int rec = read(client_socket, buffer, BUFFER_SIZE);
        if(rec < 0)
           error("Erro na leitura");
        else if(rec >0)
        {
            printf("Aqui i eh %d", i);
            pthread_mutex_lock(&lock);
            for(j = 0; j <= i; j++)
            {
                if(vetor_clientes[j] == 0)
                    continue;
                
                sock_aux = vetor_clientes[j];
                if(write(sock_aux, buffer, strlen(buffer)) < 0)
                    error("Erro na escrita");
            }
            pthread_mutex_unlock(&lock);
        }
                
    }
    return NULL;
}

/*
void func()
{
    bzero(buffer, BUFFER_SIZE);   //Limpar buffer

        //Lê o que o cliente escreveu
        if(read(newSockFd, buffer, BUFFER_SIZE) < 0)
            error("Erro na leitura");

        printf("CLiente: %s", buffer);
    
        bzero(buffer, BUFFER_SIZE);   //Limpar buffer

        fgets(buffer, BUFFER_SIZE, stdin);

        if(write(newSockFd, buffer, strlen(buffer)) < 0)
        {
            error("Erro na escrita");
        }

        if(strcmp("TERMINAR", buffer) == 0)
            break;
}*/