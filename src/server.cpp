#include "server/server.hpp"

#include <csignal>
#include <iostream>
Server* server;

void kill(int) {
    server->kill();
}

int main() {
    server = new Server("cli-tcp-chat-server.conf");
    std::signal(SIGINT, kill);
    std::signal(SIGTERM, kill);
    std::signal(SIGHUP, kill);
    server->run();
    delete server;
    return 0;
}