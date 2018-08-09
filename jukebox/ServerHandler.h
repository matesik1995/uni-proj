//
// Created by matesik on 20.01.18.
//

#ifndef SERVERHANDLER_H
#define SERVERHANDLER_H


static const int BACKLOG_SIZE = 10;

//#include "Core.h"
#include "Handler.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include <fcntl.h>
#include "IOLoop.h"
#include "ClientHandler.h"

class ServerHandler : Handler {
    int fd;
public:
    explicit ServerHandler(uint16_t port);
    int handle(epoll_event e) override;
};


#endif //SERVERHANDLER_H
