#include "./global-controler.hpp"

std::vector<std::string> GlobalControler::messageHistory = std::vector<std::string>{};

void GlobalControler::addNewMessage(std::string newMessage) {
    GlobalControler::messageHistory.push_back(newMessage);
}
