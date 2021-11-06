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
    void setup();
    void clientHandlerLoop(int currConnectionFileDescriptor);

    void threadHandlerRoutine();
    void readConfigs();

   public:
    Server(std::string configFilePath);
    ~Server();
    void run();
};