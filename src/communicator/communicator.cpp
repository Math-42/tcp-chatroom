#include "./communicator.hpp"

#include <iostream>

Communicator *Communicator::instance{nullptr};
std::mutex Communicator::mutex;

Communicator *Communicator::getInstance(int port, int maxMessageSize, std::string address, std::string user) {
    std::lock_guard<std::mutex> lock(mutex);
    if (instance == nullptr) {
        instance = new Communicator(port, maxMessageSize, address, user);
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

Communicator::Communicator(int port, int maxMessageSize, std::string address, std::string user)
    : maxMessageSize{maxMessageSize},
      port{port},
      address{address},
      user{user} {
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
    std::stringstream configs;

    configs << "PORT:     " << port
            << "\nADDRESS:  " << address
            << "\nUSERNAME: " << user;

    GlobalControler::addNewMessage(configs.str());
    GlobalControler::addNewMessage(message);

    std::string greeting = ">> " + user + " entrou no chat! <<";
    greeting.resize(maxMessageSize);
    send(clientSocket->getFileDescriptor(), greeting.data(), greeting.size(), 0);
}

void Communicator::onReceive(char *message) {
    GlobalControler::addNewMessage(message);
}

void Communicator::disconnect() {
    std::string goodbye = ">> " + user + " saiu do chat! <<";
    send(clientSocket->getFileDescriptor(), goodbye.data(), goodbye.size(), 0);
}

void Communicator::sendMessage(std::string message) {
    message.resize(maxMessageSize);
    Message newMessage(user, message);
    send(clientSocket->getFileDescriptor(), newMessage.data.data(), newMessage.size, 0);
}
