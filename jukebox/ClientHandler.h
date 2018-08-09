//
// Created by matesik on 21.01.18.
//

#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include "Handler.h"
#include <netinet/in.h>
#include <string>

const static int BUFFER_SIZE = 4;

class ClientHandler : Handler {
    int fd;
    char buffer[BUFFER_SIZE];
    ssize_t received;
    bool voted;
public:
    ClientHandler(int fd);

    int handle(epoll_event e) override;

    void sendMessage(int code, std::string msg);

    void setVoted(bool voted);

    bool getVoted();
};


#endif //CLIENTHANDLER_H
