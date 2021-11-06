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

struct clientes
{
    int ID;
    int socketfd;
    char nome[32];
};

struct clientes vetor_clientes[num_clientes];
int i = -1;

pthread_mutex_t lock;

void error(const char *msg_error)
{
    perror(msg_error);
    exit(1);
}

void adiciona_cliente(struct clientes cli)
{
    i++;
    if(i == num_clientes)
        error("Numero maximo de clientes atingido");

    cli.ID = i;
    vetor_clientes[i] = cli;
}

void envia_msg(char *msg, int id)
{
    pthread_mutex_lock(&lock);

    for(int j = 0; j <= i; j++)
    {
        if(vetor_clientes[j].ID != id)
        {
            printf("\nAgora a pessoa de ID %d vai enviar para %d de socket %d\n", id, vetor_clientes[j].ID, vetor_clientes[j].socketfd);
            if(write(vetor_clientes[j].socketfd, msg, strlen(msg)) < 0)
            {
				error("ERRO ao enviar msgs");
				break;
            }
        }
    }
    pthread_mutex_unlock(&lock);
}

void str_arruma_string (char* str, int tam) {
  int j;
  for (j = 0; j < tam; j++) { // trim \n
    if (str[i] == '\n') {
      str[i] = '\0';
      break;
    }
  }
}

void *thread_servidor(void *arg);

int main(int argc, char *argv[])
{
    //Recebe o nome do arquivo e numero de PORT
    if(argc < 2)
        error("ERRO: Insira o nome do arquivo e o nro do PORT");

    pthread_t t;
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

    newSockFd = -4;
    //Agora o programa entra em loop, e faz o que deve ser feito
    while(1)
    {
        //Aceitar a conexão
        newSockFd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if(newSockFd < 0)
            error("Erro ao aceitar clizente");
        else{
        
            if(i > num_clientes)
                error("Numero maximo de clientes atingido");

            /*Adicionar novo cliente */
            struct clientes cli;
            cli.socketfd = newSockFd;
            adiciona_cliente(cli);

            //Adiciona thread
            pthread_create(&t, NULL, thread_servidor, NULL);
        }
        for(int k = 0; k <= i; k++)
        {
            printf("\n\n Usuario %d", vetor_clientes[k].ID);
            printf("\nRespectivo socket: %d\n\n", vetor_clientes[k].socketfd);
        }
        //sleep(1);
    }

    close(newSockFd);
    close(sockfd);
    return 0;
}

void *thread_servidor(void *arg)
{
    char buffer[BUFFER_SIZE];

    struct clientes cli_aqui = vetor_clientes[i];
    //No futuro inserir manipulação do nome aqui

    bzero(buffer, BUFFER_SIZE);

    while(1)
    {
        int receive = recv(cli_aqui.socketfd, buffer, BUFFER_SIZE, 0);
        if (receive > 0)
        {
            //printf("HEA BROW\n");
			if(strlen(buffer) > 0)
            {
			    envia_msg(buffer, cli_aqui.ID);
				str_arruma_string(buffer, strlen(buffer));
				//printf("%s\n", buffer);
			}
		} 
        else if (receive == 0 || strcmp(buffer, "exit") == 0)
        {   
            strcpy(buffer, "pessoa saiu");
			//sprintf(buffer, "%d has left\n", cli_aqui.ID);
			printf("%s", buffer);
			envia_msg(buffer, cli_aqui.ID);
            return NULL;
		} else {
			error("ERRO ao receber msg");
		}

		bzero(buffer, BUFFER_SIZE);
    }
}
