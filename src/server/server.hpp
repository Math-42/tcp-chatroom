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

protected:
	virtual void setup();
	virtual void loop();
	virtual void destroy();

private:
	void threadHandlerRoutine();
	void readConfigs();

public:
	void run();
}