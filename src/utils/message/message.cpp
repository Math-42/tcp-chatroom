#include "message.hpp"

Message::Message(std::string sender, std::string content) {
    std::time_t now = time(0);

    struct tm* timeinfo;
    char buffer[80];

    time(&now);
    timeinfo = localtime(&now);

    strftime(buffer, 80, "%d/%m/%y %I:%M%p", timeinfo);

    data += "[" + std::string(buffer) + "]\n" + sender + ": " + content;
    size = data.length() + 1;
}

Message::Message(std::string content) {
    std::time_t now = time(0);
    std::string date = std::ctime(&now);
    date.pop_back();

    data += "[" + date + "]: " + content;
    size = data.length() + 1;
}