#pragma once
#include "../socket/socket.hpp"
class Client {
   private:
    int port;
    int maxMessageSize;
    bool isRunning;
    Socket* clientSocket;

   private:
    void onReceive(char* message);
    void onConnect(char* message);

   public:
    Client(int port, int maxMessageSize, std::string address);
    ~Client();
    void sendMessage(char* message);
    void run();
};