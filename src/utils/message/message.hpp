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
    Message(std::string sender, std::string content);
    Message(std::string content);
};
