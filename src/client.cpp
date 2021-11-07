#include "communicator/communicator.hpp"
#include "gui/window.hpp"

int main() {
    Communicator* communicator = Communicator::getInstance(3050, 80, "127.0.0.1");
    Window clientWindow(50, 50, 1);
    clientWindow.show();
    communicator->run();
    return 0;
}