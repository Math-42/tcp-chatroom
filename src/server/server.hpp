#include <string>
#include <fstream>
#include <map>

class Server
{
private:
	std::string configFilePath;
	std::map<std::string, int> configs;

	int maxMessageSize;
	int port;
	int maxConnections;
	bool isRunning;

private:
	void readConfigs();

public:
	void run();
}