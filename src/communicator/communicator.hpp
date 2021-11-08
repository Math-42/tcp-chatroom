#pragma once
#include <csignal>
#include <mutex>
#include <sstream>

#include "../socket/socket.hpp"
#include "../utils/global-controler/global-controler.hpp"

class Communicator {
   private:
    int port;
    bool isRunning;
    std::string address;
    std::string user;
    Socket* clientSocket;
    static Communicator* instance;
    static std::mutex mutex;

   private:
    /**
	* Construtor privado do comunicador
	* @param port porta que irá se conectar
	* @param maxMessageSize tamanho máximo das mensagens que serão recebidas e enviadas
	* @param address endereço para se conectar
	* @param user nome do usuário que será utilizado
	*/
    Communicator(int port, int maxMessageSize, std::string address, std::string user);

    /**
	 * Função que é executada toda vez que uma mensagem é recebida
	 * @param message mensagem recebida
	 */
    void onReceive(char* message);

    /**
	 * Função que é executada quando o comunicador se conecta com o servidor
	 * @param message mensagem recebida na conexão
	 */
    void onConnect(char* message);

   public:
    int maxMessageSize;
    /**
	 * Função para pegar a instância global do comunicador
	 * @return Instância global do comunicador
	 */
    static Communicator* getInstance();

    /**
	 * Função para pegar a instância global do comunicador e inicializa-lo caso não tenha sido
	 * @param port porta que irá se conectar
	 * @param maxMessageSize tamanho máximo das mensagens que serão recebidas e enviadas
	 * @param address endereço para se conectar
	 * @param user nome do usuário que será utilizado
	 * @return Instância global do comunicador
	 */
    static Communicator* getInstance(int port, int maxMessageSize, std::string address, std::string user);

    /**
	 * Função que será executada quando o comunicador desconectar
	 */
    void disconnect();

    /**
	 * Destrutor do comunicador
	 */
    ~Communicator();

    /**
	 * Envia uma mensagens para o servidor
	 * @param message mensagem que será enviada
	 */
    void sendMessage(std::string message);

    /**
	 * Inicia a comunicação com o servidor e faz o setup inicial
	 */
    void run();
};