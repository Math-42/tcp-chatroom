#include <stdio.h>
#include <math.h>

typedef struct{
    char nickname[10];
    int message[20];
} data_packet;

void encode_h(char *message, data_packet *data){

    // Pega uma LETRA e converte para o numero correspondente na tabela ASCII
    int bin = (int)message[0]-97;
    
    // Converte o numero decimal obtido para binario
    int binary[10];
    for(int i=0; i<=3; i++){
        binary[i] = bin%2;
        bin /= 2;
    }

    // Utiliza o binario obtido para preencher o pacote hamming
    data->message[0] = binary[3];
    for(int i=0; i<3; i++)
        data->message[(int)pow(2,i)] = binary[2-i];
   
    data->message[6] = data->message[4]^data->message[2]^data->message[0];
    data->message[5] = data->message[4]^data->message[1]^data->message[0];
    data->message[3] = data->message[2]^data->message[1]^data->message[0];
}

void decode_h(data_packet *data){
    char message;
    int decimal=0;

    // Inserindo erro
    data->message[1] = 1;

    // Pega os binarios que formam a mensagem do pacote hamming e converte para decimal
    decimal += 8*(data->message[0]);
    for(int i=0; i<3; i++)
        decimal += pow(2,2-i)*(data->message[(int)pow(2,i)]);
    decimal += 97;

    // Converte o decimal obtido para o char referente da tabela ASCII
    message = (char)decimal;
    printf("Mensagem recebida: %d - %c\n", decimal, message);

    // Checa por erros
    int p1, p2, p4;
    p1 = data->message[6]^data->message[4]^data->message[2]^data->message[0];
    p2 = data->message[5]^data->message[4]^data->message[1]^data->message[0];
    p4 = data->message[3]^data->message[2]^data->message[1]^data->message[0];
    
    int p = 4*p4 + 2*p2 + p1;
    if(p==0)
        printf("Nenhum erro encontrado!\n");
    else{
        printf("Erro na posição %d\n", p);
        if(data->message[7-p] == 0)
            data->message[7-p] = 1;
        else
            data->message[7-p] = 0;

        decimal=0;
        decimal += 8*(data->message[0]);
        for(int i=0; i<3; i++)
            decimal += pow(2,2-i)*(data->message[(int)pow(2,i)]);
        decimal += 97;
    
        message = (char)decimal;
        printf("Mensagem corrigida: %d - %c\n", decimal, message);
    }
}