#include <csignal>

#include "communicator/communicator.hpp"
#include "gui/window.hpp"

Window* clientWindow;
Communicator* communicator;

// função para encerrar o programa
void kill(int) {
    communicator->disconnect();
    delete communicator;
    delete clientWindow;
    exit(0);
}

// função mock
void nothing(int) {}

int main(int argc, char* argv[]) {
    //usa o nome anom caso um nome não tenha sido passado
    std::string userName = (argc >= 2) ? argv[1] : "anom";

    communicator = Communicator::getInstance(4040, 256, "127.0.0.1", userName);

    clientWindow = new Window(1);

    // cadastra os sinais para garantir que o programa finalize corretamente
    std::signal(SIGWINCH, nothing);
    std::signal(SIGINT, kill);
    std::signal(SIGTERM, kill);
    std::signal(SIGHUP, kill);

    clientWindow->show();
    communicator->run();

    return 0;
}