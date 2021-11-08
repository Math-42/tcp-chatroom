#include <csignal>

#include "communicator/communicator.hpp"
#include "gui/window.hpp"

Window* clientWindow;
Communicator* communicator;

void kill(int) {
    communicator->disconnect();
    delete communicator;
    delete clientWindow;
}

void nothing(int) {}

int main(int argc, char* argv[]) {
    std::string userName = (argc >= 2) ? argv[1] : "anom";

    communicator = Communicator::getInstance(4040, 256, "127.0.0.1", userName);

    clientWindow = new Window(50, 50, 1);
    std::signal(SIGWINCH, nothing);
    std::signal(SIGINT, kill);
    std::signal(SIGTERM, kill);
    std::signal(SIGHUP, kill);

    clientWindow->show();
    communicator->run();

    return 0;
}