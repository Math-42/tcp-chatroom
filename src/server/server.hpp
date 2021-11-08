#pragma once
#include <cstring>
#include <fstream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

#include "../socket/socket.hpp"

class Server {
   private:
    std::string configFilePath;
    std::map<std::string, int> configs;
    std::vector<int> connections;
    Socket *serverSocket;
    struct sockaddr_in serverAddr;
    bool isRunning;

   private:
    /**
	 * Faz o setup inicial do servidor
	 */
    void setup();

    /**
	 * Loop que lida com cada thread de cada cliente
	 * @param currConnectionFileDescriptor file descriptor do socket com o client atual
	 */
    void clientHandlerLoop(int currConnectionFileDescriptor);

    /**
	 * Loop que espera pela conexão de cada client e da a eles uma thread própria
	 */
    void threadHandlerRoutine();

    /**
	 * Lê as configurações da conf file do servidor
	 */
    void readConfigs();

   public:
    /**
	 * Encerra todas as conexões de cada um dos usuários e encerra o servidor
	 */
    void kill();

    /**
	 * Constructor do servidor
	 * @param configFilePath path do arquivo de configurações
	 */
    Server(std::string configFilePath);

    /**
	 * Faz o setup do servidor e inicializa suas funcionalidades
	 */
    void run();
};