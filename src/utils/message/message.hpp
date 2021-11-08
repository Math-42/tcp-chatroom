#pragma once
#include <time.h>

#include <chrono>
#include <string>
#include <vector>
class Message {
   public:
    std::string data;
    int size;

   public:
    /**
	 * Construtor que insere um remetente e uma data na mensagem
	 * @param sender remetente da mensagem
	 * @param content conteúdo da mensagem
	 */
    Message(std::string sender, std::string content);

    /**
	 * Construtor que cria uma mensagem apenas com conteúdo e data
	 * @param content conteúdo da mensagem
	 */
    Message(std::string content);
};
