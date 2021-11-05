#pragma once
#include <string>
#include <fstream>
#include <map>
#include <pthread.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <linux/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
class Server
{
private:
	std::string configFilePath;
	std::map<std::string, int> configs;
	struct sockaddr_int serverAddr();
	int maxMessageSize;
	int port;
	int maxConnections;
	bool isRunning;

protected:
	virtual void setup();
	virtual void loop();
	virtual void destroy();

private:
	void threadHandlerRoutine();
	void readConfigs();

public:
	void run();
};