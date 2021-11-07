#include "./global-controler.hpp"

std::vector<Message> GlobalControler::messageHistory = std::vector<Message>{};
std::vector<std::string> GlobalControler::allChats = std::vector<std::string>{};
std::vector<std::string> GlobalControler::currUsers = std::vector<std::string>{};

void GlobalControler::addNewMessage(Message newMessage) {
    GlobalControler::messageHistory.push_back(newMessage);
}

void GlobalControler::updateCurrUsers(std::vector<std::string> newCurrUsers) {
    GlobalControler::currUsers.clear();
    GlobalControler::currUsers.insert(GlobalControler::currUsers.end(), newCurrUsers.begin(), newCurrUsers.end());
}