#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define TAMANHO_msg 255
#define TAMANHO_buff 287

// Variaveis globais dos usuarios
int sockfd = 0;
int flag = 0;
char name[32];

void error(const char *msg_error)
{
    perror(msg_error);
    exit(1);
}

void prepara_stdout() 
{
    printf("%s", "> ");
    fflush(stdout);
}

//Função que deixa a msg de entrada pronta
void formata_string_entrada (char* arr, int length) 
{
    int i;
    for (i = 0; i < length; i++)
    if (arr[i] == '\n')
    {
        arr[i] = '\0';
        break;
    }
}

void catch_ctrl_c_and_exit(int sig) 
{
    flag = 1;
}

void *envia_msg(void* arg)
{
    char msg[TAMANHO_msg];
	char buffer[TAMANHO_buff];

    bzero(msg, TAMANHO_msg);
    bzero(buffer, TAMANHO_buff);

    while(1)
    {
  	    prepara_stdout();
        fgets(msg, TAMANHO_msg, stdin);
        formata_string_entrada(msg, TAMANHO_msg);

        if (strcmp(msg, "SAIR") == 0) //Condição de parada
            break;
        else if(strlen(msg) > TAMANHO_buff)
        {
            printf("\nSistema: Sua msg é muito grande para ser enviada!");
            prepara_stdout();
        }    
        else 
        {
            //Preparar msg a ser enviada!
            strcpy(buffer, name);
            strcat(buffer, ": ");
            strcat(buffer, msg);
            strcat(buffer, "\0");

            //printf("\n A msg aqui: %s \n", buffer);
            send(sockfd, buffer, strlen(buffer), 0);
        }

		bzero(msg, TAMANHO_msg);
        bzero(buffer, TAMANHO_buff);
  }

  catch_ctrl_c_and_exit(2);
  return NULL;
}

void *recebe_msg(void* arg) 
{
	char buffer[TAMANHO_buff];
    bzero(buffer, TAMANHO_buff);

    while (1) 
    {
		int rec = recv(sockfd, buffer, TAMANHO_buff, 0);
        if (rec > 0) 
        {
            printf("%s", buffer);
            printf("\n");
            prepara_stdout();
        } 
        else if (rec == 0) 
			break;
        else
        {
            printf("\nErro ao receber msg\n");
            prepara_stdout(); 
        }
        bzero(buffer, TAMANHO_buff);
  }

  return NULL;
}

int main(int argc, char **argv)
{
	if(argc != 2)
        error("ERRO: Insira o port como argumento");

	char ip[11], msg[50];
    strcpy(ip, "127.0.0.1\0");
	int port = atoi(argv[1]);

    //Adiciona o sinal de saída do programa
	signal(SIGINT, catch_ctrl_c_and_exit);

    //Inserção do nome 
	printf("Por favor, insira seu nome: ");
    fgets(name, 32, stdin);
    formata_string_entrada(name, strlen(name));

    //Teste de consistência do nome
    if(strlen(name) > 32 || strlen(name) < 2)
		error("O nome precisa ter entre 2 e 32 caracteres\n");

    //Iniciar configurações do socket
	struct sockaddr_in server_addr;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    server_addr.sin_port = htons(port);


    // Buscar conexão com servidor
    int conec = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (conec == -1)
		error("ERROR: connect\n");


    /****** Conexão estabelecida *******/
	// Envia o nome
	send(sockfd, name, 32, 0);

	printf("--------CHATROOM--------\n");

    //Inicia configurações da threads do cliente
	pthread_t envia, recebe;
    if(pthread_create(&envia, NULL,envia_msg, NULL) != 0 
        || pthread_create(&recebe, NULL, recebe_msg, NULL) != 0)
        error("ERRO ao iniciar threads do cliente");
    
	while (1)
    {
		if(flag)
        {
			printf("\nAté logo!\n");
			break;
        }
	}

	close(sockfd);
	return 0;
}