#pragma once
#include <string>
#include <fstream>
#include <map>
#include <cstring>
#include <sstream>
#include "../socket/socket.hpp"
#include <vector>
#include <thread>
#include <stdexcept>

class Server
{
private:
	std::string configFilePath;
	std::map<std::string, int> configs;
	std::vector<int> connections;
	Socket *serverSocket;
	struct sockaddr_in serverAddr;
	bool isRunning;

public:
	void setup();
	void clientHandlerLoop(int currConnectionFileDescriptor);
	
private:
	void threadHandlerRoutine();
	void readConfigs();

public:
	Server(std::string configFilePath);
	~Server();
	void run();
};