#include "server/server.hpp"

int main()
{
	Server server("config/cli-tcp-chat-server.conf");
	server.run();
	return 0;
}