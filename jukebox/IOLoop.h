//
// Created by matesik on 20.01.18.
//

#ifndef IOLOOP_H
#define IOLOOP_H

#include <sys/epoll.h>
#include <cstdio>
#include <cstdlib>
#include <zconf.h>
#include <map>
#include "Handler.h"
#include "logger.h"

static const int MAX_EVENTS = 32;

class IOLoop {
    std::map<int, Handler*> handlers;
    int epfd;
    struct epoll_event events[MAX_EVENTS];
public:
    IOLoop();
    void addHandler(int fd, Handler* handler, unsigned int events);
    void removeHandler(int fd);
    void start();
};


#endif //IOLOOP_H
