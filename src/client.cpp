#include "client/client.hpp"

int main()
{
	Client client(3090, 80, "127.0.0.1");
	client.run();
	return 0;
}