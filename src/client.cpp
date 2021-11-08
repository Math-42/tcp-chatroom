#include <iostream>

#include "communicator/communicator.hpp"
#include "gui/window.hpp"

int main(int argc, char* argv[]) {
    std::string userName = (argc >= 2) ? argv[1] : "anom";

    Communicator* communicator = Communicator::getInstance(4040, 256, "127.0.0.1", userName);
    Window clientWindow(50, 50, 1);

    clientWindow.show();
    communicator->run();

    return 0;
}