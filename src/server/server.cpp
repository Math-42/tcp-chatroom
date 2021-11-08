#include "./server.hpp"

#include <algorithm>
#include <iostream>

Server::Server(std::string configFilePath) {
    this->configFilePath = configFilePath;
    readConfigs();
    serverSocket = new Socket(std::string(""), configs["PORT"]);
}

void Server::readConfigs() {
    std::fstream configurationFile(configFilePath);

    if (!configurationFile.is_open()) {
        throw std::runtime_error("Não foi possivel abrir o arquivo de configurações\n");
        return;
    }

    std::string key;
    char tempChar;
    std::string line;
    int value;

    std::cout << "Lendo arquivo de configurações:" << std::endl;

    while (getline(configurationFile, line)) {
        std::stringstream parsedLine(line);
        parsedLine >> key;
        parsedLine >> tempChar;
        parsedLine >> value;

        configs[key] = value;
        std::cout << key << ": " << value << std::endl;
    }
}

void Server::threadHandlerRoutine() {
    int connectionFileDescriptor;

    //Espera até uma conexão aparecer e aceita
    if (isRunning > 0 && !serverSocket->acceptConnection(connectionFileDescriptor)) {
        printf("Falha na conexão\n");
        return;
    }
    connections.push_back(connectionFileDescriptor);

    std::thread currClientThread(&Server::clientHandlerLoop, this, connectionFileDescriptor);
    currClientThread.detach();
}

void Server::setup() {
    serverSocket->bind();
    serverSocket->listen(configs["MAX_CONNECTIONS"]);
}

void Server::clientHandlerLoop(int currConnectionFileDescriptor) {
    send(currConnectionFileDescriptor, "Conexão recebida com sucesso", configs["MAX_MESSAGE_SIZE"], 0);
    printf("Iniciando conexão com o cliente %d\n", currConnectionFileDescriptor);

    int receivedBytes;

    while (1) {
        char message[configs["MAX_MESSAGE_SIZE"]];
        std::memset(&message, 0, configs["MAX_MESSAGE_SIZE"]);

        receivedBytes = recv(currConnectionFileDescriptor, message, configs["MAX_MESSAGE_SIZE"], 0);

        if (receivedBytes <= 0) break;

        printf("Recebido do cliente %d: %s\n", currConnectionFileDescriptor, message);

        for (auto client : connections) {
            send(client, message, configs["MAX_MESSAGE_SIZE"], 0);
            printf("Enviando para o cliente  %d: %s\n", client, message);
        }
    };

    connections.erase(std::remove(connections.begin(), connections.end(), currConnectionFileDescriptor), connections.end());
    printf("Fechando conexão com o cliente: %d\n", currConnectionFileDescriptor);
    close(currConnectionFileDescriptor);
}

Server::~Server() {
    serverSocket->close();
    delete serverSocket;
    std::cout << "Encerrando o servidor" << std::endl;
}

void Server::run() {
    isRunning = true;
    setup();
    while (isRunning) {
        threadHandlerRoutine();
    };
    isRunning = false;
}