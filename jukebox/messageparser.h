#ifndef MESSAGEPARSER_H
#define MESSAGEPARSER_H

#include "ClientHandler.h"

class MessageParser
{
public:
    MessageParser() = default;
    static void parse(ClientHandler* client, char* msg);
};

#endif // MESSAGEPARSER_H
