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
    Socket(std::string address, unsigned short port);
    ~Socket();

    void bind();
    void listen(int maxNumberOfConnections);
    bool acceptConnection(int &connectionFileDescriptor);
    void connect();
    void close();

    int getFileDescriptor();
};