#pragma once
#include <string>
#include <vector>

#include "../message/message.hpp"

class GlobalControler {
   public:
    static std::vector<std::string> messageHistory;

   public:
    /**
	 * Adiciona uma nova mensagem no vetor de mensagens
	 * @param newMessage mensagem que será adicionada
	 */
    static void addNewMessage(std::string newMessage);
};