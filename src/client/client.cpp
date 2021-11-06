#include "./client.hpp"

#include <iostream>

Client::Client(int port, int maxMessageSize, std::string address)
    : maxMessageSize{maxMessageSize},
      port{port} {
    clientSocket = new Socket(address, port);
};

Client::~Client() {
    clientSocket->close();
    delete clientSocket;
}

void Client::run() {
    isRunning = true;
    clientSocket->connect();
    char initialMessage[maxMessageSize];

    read(clientSocket->getFileDescriptor(), initialMessage, sizeof(initialMessage));
    onConnect(initialMessage);

    while (isRunning) {
        char message[maxMessageSize];
        if (recv(clientSocket->getFileDescriptor(), message, sizeof(message), 0) <= 0) {
            break;
        }
        onReceive(message);
    }

    isRunning = false;
}

void Client::onConnect(char *message) {
    std::cout << message << std::endl;
}

void Client::onReceive(char *message) {
    std::cout << message << std::endl;
}

void Client::sendMessage(char *message) {
    send(clientSocket->getFileDescriptor(), message, sizeof(*message), 0);
}
