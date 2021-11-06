#pragma once
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <stdexcept>

class Socket
{

private:
	int fileDescriptor;
	bool isClosed;
	struct sockaddr_in socketAddr;
	std::string address;

public:
	Socket(std::string address, unsigned short port);
	~Socket();
	void makeBind();
	void startListen(int maxNumberOfConnections);
	bool acceptConnection(int &connectionFileDescriptor);
	void makeConnection();
	void closes();
	int getFileDescriptor();
};