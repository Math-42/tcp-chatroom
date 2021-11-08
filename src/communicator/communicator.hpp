#pragma once
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
    Communicator(int port, int maxMessageSize, std::string address, std::string user);
    void onReceive(char* message);
    void onConnect(char* message);

   public:
    int maxMessageSize;
    static Communicator* getInstance();
    static Communicator* getInstance(int port, int maxMessageSize, std::string address, std::string user);
    void disconnect();
    ~Communicator();
    void sendMessage(std::string message);
    void run();
};