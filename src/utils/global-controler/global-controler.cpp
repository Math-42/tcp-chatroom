#include "./global-controler.hpp"
//inicializa variável estática que contem todas as mensagens mostradas pelo cliente
std::vector<std::string> GlobalControler::messageHistory = std::vector<std::string>{};

void GlobalControler::addNewMessage(std::string newMessage) {
    GlobalControler::messageHistory.push_back(newMessage);
}
