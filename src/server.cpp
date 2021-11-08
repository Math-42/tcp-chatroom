#include "server/server.hpp"

#include <csignal>
#include <iostream>
Server* server;

//função que finaliza o servidor
void kill(int) {
    server->kill();
    delete server;
    exit(0);
}

int main() {
    server = new Server("cli-tcp-chat-server.conf");

    //cadastra os sinais para garantir que o servidor finalize corretamente
    std::signal(SIGINT, kill);
    std::signal(SIGTERM, kill);
    std::signal(SIGHUP, kill);
    server->run();
    return 0;
}