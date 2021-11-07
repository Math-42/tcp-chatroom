#pragma once
#include<mutex>
#include "../socket/socket.hpp"
#include "../utils/global-controler/global-controler.hpp"

class Communicator {
   private:
    int port;
    int maxMessageSize;
    bool isRunning;
    Socket* clientSocket;
    static Communicator* instance;
    static std::mutex mutex;

   private:

    Communicator(int port, int maxMessageSize, std::string address);
    void onReceive(char* message);
    void onConnect(char* message);

   public:
    static Communicator *getInstance();
    static Communicator *getInstance(int port, int maxMessageSize, std::string address);
    ~Communicator();
    void sendMessage(std::string message);
    void run();
};