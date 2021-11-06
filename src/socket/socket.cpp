#include "./socket.hpp"

#include <iostream>

Socket::Socket(std::string address, unsigned short port) : address{address} {
    fileDescriptor = socket(PF_INET, SOCK_STREAM, getprotobyname("tcp")->p_proto);

    if (fileDescriptor == -1) {
        throw std::runtime_error("Não foi possível criar o socket");
    }

    std::memset(&socketAddr, 0, sizeof(socketAddr));

    socketAddr.sin_family = AF_INET;
    socketAddr.sin_addr.s_addr = (this->address == "") ? htonl(INADDR_ANY) : inet_addr(this->address.c_str());
    socketAddr.sin_port = htons(port);
    isClosed = false;
}

Socket::~Socket() {
    close();
}

void Socket::bind() {
    int set_true = 1;

    if (::bind(fileDescriptor, (struct sockaddr *)&socketAddr, sizeof(socketAddr)) == 0)
        return;
    if (setsockopt(fileDescriptor, SOL_SOCKET, SO_REUSEADDR, &set_true, sizeof set_true) != -1)
        return;

    throw std::runtime_error("Não foi possível realizar o bind");
}

void Socket::listen(int maxNumberOfConnections) {
    if (::listen(fileDescriptor, maxNumberOfConnections) == -1) {
        throw std::runtime_error("Erro ao iniciar a escuta");
    }
}

bool Socket::acceptConnection(int &connectionFileDescriptor) {
    struct sockaddr_storage their_addr;
    socklen_t addr_size = sizeof their_addr;
    connectionFileDescriptor = accept(fileDescriptor, (struct sockaddr *)&their_addr, &addr_size);
    return connectionFileDescriptor == -1 ? false : true;
}

void Socket::connect() {
    if (::connect(fileDescriptor, (struct sockaddr *)&socketAddr, sizeof(socketAddr)) == -1) {
        throw std::runtime_error("Não foi possível se conectar");
    };
}

int Socket::getFileDescriptor() {
    return fileDescriptor;
}

void Socket::close() {
    if (!isClosed) ::close(fileDescriptor);
    isClosed = true;
}