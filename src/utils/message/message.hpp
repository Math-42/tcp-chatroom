#pragma once
#include <chrono>
#include <string>
#include <vector>
class Message {
   public:
    std::string sender;
    std::string data;
    std::string content;
    std::vector<unsigned char> binaryContent;

   public:
    Message(std::string sender, std::string content);
    Message(std::string sender, std::string data, std::string content);
    void serialize();
    std::vector<std::vector<unsigned char>> serialize(int maxSize);
    void unserialize();
};
