#pragma once
#include <sys/socket.h>


class Socket{

private:
	int fileDescriptor;
	void acceptConnection();

public:
	Socket();
	void bind();
	void listen();
	void connect();
};