#pragma once
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstring>
#include <stdexcept>
#include <string>

class Socket {
   private:
    int fileDescriptor;
    bool isClosed;
    struct sockaddr_in socketAddr;
    std::string address;

   public:
    /**
	 * Construtor do socket
	 * @param address endereço de onde se deseja conectar
	 * @param port porta que se deseja conectar
	 */
    Socket(std::string address, unsigned short port);

    /**
	 * Destrutor do socket
	 */
    ~Socket();

    /**
	 * Associa o socket a uma porta no computador
	 */
    void bind();

    /**
	 * Começa a ouvir conexões na porta pré definida
	 * @param maxNumberOfConnections número máximo de conexões que podem ficar em espera
	 */
    void listen(int maxNumberOfConnections);

    /**
	 * Aceita uma conexão na porta pré definida
	 * @param connectionFileDescriptor file descriptor da conexão feita
	 * @return retorna um boleano indicando se deu certo ou não
	 */
    bool acceptConnection(int &connectionFileDescriptor);

    /**
	 * Conecta no servidor de endereço e porta já definidos
	 */
    void connect();

    /**
	 * Fecha a conexão já estabelecida
	 */
    void close();

    /**
	 * Retorna o file descriptor do socket atual
	 */
    int getFileDescriptor();
};