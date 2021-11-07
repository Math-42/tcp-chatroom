#include "./communicator.hpp"

#include <iostream>

Communicator *Communicator::instance{nullptr};
std::mutex Communicator::mutex;

Communicator *Communicator::getInstance(int port, int maxMessageSize, std::string address) {
    std::lock_guard<std::mutex> lock(mutex);
    if (instance == nullptr) {
        instance = new Communicator(port, maxMessageSize, address);
    }
    return instance;
}

Communicator *Communicator::getInstance() {
    std::lock_guard<std::mutex> lock(mutex);
    if (instance == nullptr) {
        throw std::runtime_error("O comunicador ainda não foi inicializado");
    }
    return instance;
}

Communicator::Communicator(int port, int maxMessageSize, std::string address)
    : maxMessageSize{maxMessageSize},
      port{port} {
    clientSocket = new Socket(address, port);
};

Communicator::~Communicator() {
    clientSocket->close();
    delete clientSocket;
}

void Communicator::run() {
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

void Communicator::onConnect(char *message) {
    //std::cout << message << std::endl;
    GlobalControler::addNewMessage(Message("sender", message));
}

void Communicator::onReceive(char *message) {
    GlobalControler::addNewMessage(Message("sender", message));
    //std::cout << message << std::endl;
}

void Communicator::sendMessage(std::string message) {
    Message newMessage("curr", message);
    send(clientSocket->getFileDescriptor(), message.data(), message.size(), 0);
}
